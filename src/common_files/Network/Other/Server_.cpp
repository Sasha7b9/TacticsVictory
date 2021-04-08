// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Other/NetworkTypes_.h"
#include "Network/Other/Server_.h"


static std::vector<TaskMasterServer *> tasks;


void MasterServer::Destroy()
{
    destroy = true;

    mutex.lock();           // Ожидаем завершения ThreadConnect
    mutex.unlock();

    connOUT.Release();
}


bool MasterServer::IsConnected()
{
    return (state == State::InConnection ||
        state == State::WaitPing);
}


void MasterServer::SetCallbacks(pFuncVV fail, pFuncVV connection, pFuncVV disconnection, pFuncVI ping)
{
    funcFailConnection = fail;
    funcConnection = connection;
    funcDisconnection = disconnection;
    funcPing = ping;
}


void MasterServer::Connect()
{
    if (!funcFailConnection || !funcConnection || !funcDisconnection || !funcPing)
    {
        LOGERROR("Callbacks not defined");
        return;
    }

    if (ip.empty())
    {
        LOGERRORF("Not specified address master server");

        return;
    }

    if (state == State::Idle)
    {
        state = State::NeedConnection;
    }
}


static void ThreadConnect(ConnectorTCP *connector, pchar full_address, std::mutex *mutex,  uint8 *state)
{
    mutex->lock();

    auto [host, port] = ConnectorTCP::ParseAddress(full_address);

    if (connector->Connect(host, port))
    {
        *state = MasterServer::State::EventConnection;
        connector->SetReadTimeOut(10000);
    }
    else
    {
        *state = MasterServer::State::EventFailConnection;
    }

    mutex->unlock();
}


std::string MasterServer::GetAnswer(pchar key)
{
    mutex.lock();

    connOUT.Transmit(key);

    std::string result = connOUT.ReceiveWait();

    mutex.unlock();

    return result;
}


void MasterServer::SendString(pchar string)
{
    connOUT.Transmit(string);
}


std::string MasterServer::GetAnswer()
{
    return connOUT.Receive();
}


static void ThreadPing(ConnectorTCP *connector, std::mutex *mutex, int *ping, uint8 *state)
{
    using namespace std::chrono;
    mutex->lock();
    auto start = system_clock::now();
    connector->Transmit(MSM_PING);
    std::string result = connector->Receive();

    if (result == MSM_PING)
    {
        *state = MasterServer::State::GetPing;
        auto end = system_clock::now();
        *ping = (int)duration_cast<milliseconds>(end - start).count();
    }
    else
    {
        *state = MasterServer::State::EventDisconnect;
    }

    mutex->unlock();
}


void MasterServer::Update()
{
    static int ping = 999;

    switch (state)
    {
    case State::Idle:
        break;

    case State::NeedConnection:
        {
            if (!destroy)
            {
                if (mutex.try_lock())
                {
                    mutex.unlock();
                    state = State::AttemptConnection;
                    std::thread thread(ThreadConnect, &connOUT, std::move(ip.c_str()), &mutex, (uint8 *)&state);
                    thread.detach();
                }
            }
        }
        break;

    case State::AttemptConnection:
        break;

    case State::EventConnection:
        state = State::InConnection;
        funcConnection();
        break;

    case State::EventFailConnection:
        state = State::Idle;
        funcFailConnection();
        break;

    case State::InConnection:
        {
            using namespace std::chrono;
            static auto prev_time = system_clock::now();
            auto now = system_clock::now();
            int64 delta = duration_cast<milliseconds>(now - prev_time).count();

            if (delta >= 1000)
            {
                state = State::WaitPing;
                std::thread thread(ThreadPing, &connOUT, &mutex, &ping, (uint8 *)&state);
                thread.detach();

                prev_time = now;
            }

            int64 now_ms = duration_cast<milliseconds>(now.time_since_epoch()).count();

            ExecuteTasks(now_ms);
        }
        break;

    case State::WaitPing:
        break;

    case State::EventDisconnect:
        state = State::Idle;
        tasks.clear();
        funcPing(ping);
        funcDisconnection();
        break;

    case State::GetPing:
        state = State::InConnection;
        funcPing(ping);
        break;
    }
}


void MasterServer::ExecuteTasks(int64 now)
{
    for each (TaskMasterServer * task in tasks)
    {
        if (now >= task->prev_time + task->delta_time)
        {
            mutex.lock();

            task->func();

            task->prev_time = now;

            mutex.unlock();
        }
    }
}


void MasterServer::SetTask(TaskMasterServer *task)
{
    tasks.push_back(task);
}
