// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Other/MasterServer_.h"
#include "Network/Other/NetworkTypes_.h"


static std::vector<TaskMasterServer *> tasks;


void MasterServer::Destroy()
{
    destroy = true;

    mutex.lock();           // Ожидаем завершения ThreadConnect
    mutex.unlock();

    connector.Release();
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

    if (address.empty())
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


std::string MasterServer::GetValue(pchar key)
{
    mutex.lock();

    connector.Transmit(key);

    std::string result = connector.ReceiveWait();

    mutex.unlock();

    return result;
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
                    std::thread thread(ThreadConnect, &connector, std::move(address.c_str()), &mutex, (uint8 *)&state);
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
            long long delta = duration_cast<milliseconds>(now - prev_time).count();

            if (delta >= 1000)
            {
                state = State::WaitPing;
                std::thread thread(ThreadPing, &connector, &mutex, &ping, (uint8 *)&state);
                thread.detach();

                long long now_ms = duration_cast<milliseconds>(now.time_since_epoch()).count();

                for each (TaskMasterServer *task in tasks)
                {
                    if (now_ms >= task->prev_time + task->delta_time)
                    {
                        std::string answer = GetValue(task->request.c_str());

                        task->process(answer.c_str());
                    }
                }

                std::string livingrooms = GetValue(MSG_GET_LIVINGROMS);
                //TheMenu->pageFindServer->SetServersInfo(livingrooms);
                LOGWRITE(livingrooms.c_str());
                prev_time = now;
            }
        }
        break;

    case State::WaitPing:
        break;

    case State::EventDisconnect:
        state = State::Idle;
        funcPing(ping);
        funcDisconnection();
        break;

    case State::GetPing:
        state = State::InConnection;
        funcPing(ping);
        break;
    }
}


void MasterServer::AppendTask(TaskMasterServer *task)
{
    tasks.push_back(task);
}
