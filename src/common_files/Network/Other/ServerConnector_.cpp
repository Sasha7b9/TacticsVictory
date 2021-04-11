// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Other/NetworkTypes_.h"
#include "Network/Other/ServerConnector_.h"
#include "Utils/GlobalFunctions_.h"


static std::vector<TaskMasterServer *> tasks;


void ServerConnector::Destroy()
{
    destroy = true;

    mutex.lock();           // Ожидаем завершения ThreadConnect
    mutex.unlock();

    connector.Release();
}


bool ServerConnector::IsConnected()
{
    return (state == State::InConnection ||
        state == State::WaitPing);
}


void ServerConnector::SetCallbacks(pFuncVV fail, pFuncVV connection, pFuncVV disconnection, pFuncVI ping)
{
    funcFailConnection = fail;
    funcConnection = connection;
    funcDisconnection = disconnection;
    funcPing = ping;
}


void ServerConnector::Connect()
{
    if (!funcFailConnection || !funcConnection || !funcDisconnection || !funcPing)
    {
        LOGERROR("Callbacks not defined");
        return;
    }

    if (host.empty())
    {
        LOGERRORF("Not specified address master server");

        return;
    }

    if (state == State::Idle)
    {
        state = State::NeedConnection;
    }
}


std::string ServerConnector::GetAnswer()
{
    return connector.Receive();
}


static void ThreadConnect(ConnectorTCP *conn_out, pchar host, uint16 port, std::mutex *mutex, uint8 *state)
{
    mutex->lock();

    if (conn_out->Connect(host, port))
    {
        *state = ServerConnector::State::EventConnection;
    }
    else
    {
        *state = ServerConnector::State::EventFailConnection;
    }

    mutex->unlock();
}


std::string ServerConnector::GetAnswer(pchar key)
{
    mutex.lock();

    connector.Transmit(key);

    std::string result = connector.Receive();

    mutex.unlock();

    return result;
}


void ServerConnector::SendString(pchar string)
{
    connector.Transmit(string);
}


static void ThreadPing(ConnectorTCP *connector, std::mutex *mutex, int *ping, uint8 *state)
{
    mutex->lock();

    int64 start = GF::Timer::TimeMS();

    connector->Transmit(MSM_PING);

    std::string result = connector->Receive();

    if (result == MSM_PING)
    {
        *state = ServerConnector::State::GetPing;
        *ping = (int)(GF::Timer::TimeMS() - start);
    }
    else
    {
        *state = ServerConnector::State::EventDisconnect;
    }

    mutex->unlock();
}


void ServerConnector::Update()
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
                    std::thread thread(ThreadConnect, &connector, std::move(host.c_str()), port,
                        &mutex, (uint8 *)&state);
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
            static int64 prev_time = GF::Timer::TimeMS();

            int64 delta = GF::Timer::TimeMS() - prev_time;

            if (delta >= 1000)
            {
                state = State::WaitPing;
                std::thread thread(ThreadPing, &connector, &mutex, &ping, (uint8 *)&state);
                thread.detach();

                prev_time = GF::Timer::TimeMS();
            }

            ExecuteTasks();
        }
        break;

    case State::WaitPing:

        ExecuteTasks();

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


void ServerConnector::ExecuteTasks()
{
    int64 now = GF::Timer::TimeMS();

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


void ServerConnector::SetTask(TaskMasterServer *task)
{
    tasks.push_back(task);
}
