// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Other/NetworkTypes_.h"
#include "Network/Other/ServerConnector_.h"
#include "Utils/GlobalFunctions_.h"


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


void ServerConnector::Destroy()
{
    destroy = true;

    mutex.lock();           // ������� ���������� ThreadConnect
    mutex.unlock();

    connector.Release();
}


bool ServerConnector::IsConnected()
{
    return (state == State::InConnection);
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


uint ServerConnector::SendRequest(pchar request, const void *buffer, uint size_buffer)
{
    mutex.lock();

    last_request_id++;

    connector.Transmit(&last_request_id, 4);

    uint size_full = (uint)std::strlen(request) + size_buffer + 1;

    connector.Transmit(&size_full, 4);

    connector.Transmit(request, (uint)std::strlen(request) + 1);

    if (buffer)
    {
        connector.Transmit(buffer, size_buffer);
    }

    mutex.unlock();

    return last_request_id;
}


void ServerConnector::Update()
{
    static int ping = 999;

    ReceiveData();

    ProcessData();

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
                    std::thread thread(ThreadConnect, &connector, std::move(host.c_str()), port, &mutex, (uint8 *)&state);
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
        ExecuteTasks();
        break;

    case State::EventDisconnect:
        state = State::Idle;
        all_tasks.clear();
        funcPing(ping);
        funcDisconnection();
        break;

    case State::GetPing:
        state = State::InConnection;
        funcPing(ping);
        break;
    }
}



void ServerConnector::ReceiveData()
{
    mutex.lock();

    static const uint SIZE_CHUNK = 1024;

    uint8 buffer[SIZE_CHUNK];

    uint received = connector.Receive(buffer, SIZE_CHUNK);

    while (received > 0)
    {
        data.insert(data.begin(), buffer, &buffer[received]);

        received = connector.Receive(buffer, SIZE_CHUNK);
    }

    mutex.unlock();
}


void ServerConnector::ProcessData()
{

}


void ServerConnector::ExecuteTasks()
{
    int64 now = GF::Timer::TimeMS();

    for each (TaskMasterServer * task in all_tasks)
    {
        if (now >= task->prev_time + task->delta_time)
        {
            mutex.lock();

            uint id = task->request();

            task->prev_time = now;

            if (task->handler_answer)
            {
                active_tasks[id] = task;
            }

            mutex.unlock();
        }
    }
}


void ServerConnector::SetTask(TaskMasterServer *task)
{
    all_tasks.push_back(task);
}
