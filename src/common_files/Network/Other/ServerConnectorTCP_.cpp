// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Other/NetworkTypes_.h"
#include "Network/Other/ServerConnectorTCP_.h"
#include "Utils/GlobalFunctions_.h"
#include <climits>
#include <thread>


static void ThreadConnect(ConnectorTCP *conn_out, pchar host, uint16 port, std::mutex *mutex, uint8 *state)
{
    mutex->lock();

    if (conn_out->Connect(host, port))
    {
        *state = ServerConnectorTCP::State::EventConnection;
    }
    else
    {
        *state = ServerConnectorTCP::State::EventFailConnection;
    }

    mutex->unlock();
}


void ServerConnectorTCP::Destroy()
{
    destroy = true;

    mutex.lock();           // ќжидаем завершени€ ThreadConnect
    mutex.unlock();

    connector.Release();
}


bool ServerConnectorTCP::IsConnected()
{
    return (state == State::InConnection);
}


void ServerConnectorTCP::SetCallbacks(pFuncVV fail, pFuncVV connection, pFuncVV disconnection)
{
    funcFailConnection = fail;
    funcConnection = connection;
    funcDisconnection = disconnection;
}


void ServerConnectorTCP::Connect()
{
    if (!funcFailConnection || !funcConnection || !funcDisconnection)
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


void ServerConnectorTCP::Disconnect()
{
    if (IsConnected())
    {
        mutex.lock();
        connector.Disconnect();
        mutex.unlock();

        state = State::EventDisconnect;
    }
}


uint ServerConnectorTCP::SendRequest(pchar request, const void *buffer, uint size_buffer)
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


uint ServerConnectorTCP::SendRequest(pchar request, pchar _data)
{
    return SendRequest(request, _data, (uint)std::strlen(_data) + 1);
}


void ServerConnectorTCP::Update()
{
    ReceiveData();

    ProcessData();

    if (!ExistConnection())
    {
        Disconnect();
    }

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
        funcDisconnection();
        break;

    case State::GetPing:
        state = State::InConnection;
        break;
    }
}



void ServerConnectorTCP::ReceiveData()
{
    if (!IsConnected())
    {
        return;
    }

    mutex.lock();

    static const int SIZE_CHUNK = 1024;

    char buffer[SIZE_CHUNK];

    ssize_t received = connector.Receive(buffer, SIZE_CHUNK);

    while (received > 0)
    {
        data.insert(data.end(), buffer, buffer + received);

        received = connector.Receive(buffer, SIZE_CHUNK);
    }

    mutex.unlock();
}


void ServerConnectorTCP::ProcessData()
{
    while (data.size() > 4 + 4)        // ≈сли прин€то данных больше чем id и количество байт в сообщении
    {
        uint id = *((uint *)data.data());

        uint size_answer = *((uint *)(data.data() + 4));

        if (data.size() >= 4 + 4 + size_answer)
        {
            auto it = active_tasks.find(id);

            if (it != active_tasks.end())
            {
                pchar answer = (pchar)data.data() + 4 + 4;

                void *buffer = nullptr;

                uint size_buffer = 0;

                if (std::strlen(answer) + 1 < size_answer)
                {
                    buffer = data.data() + 4 + 4 + std::strlen(answer) + 1;

                    size_buffer = size_answer - (uint)std::strlen(answer) - 1;
                }

                TaskMasterServer *task = it->second;

                task->handler_answer(answer, buffer, size_buffer);

                task->last_tive_receive = GF::Timer::TimeMS();
            }
            else
            {
                LOGERRORF("Handler for id %d not found", id);
            }

            data.erase(data.begin(), data.begin() + 4 + 4 + size_answer);
        }
        else
        {
            break;          // ≈сли не прин€ты все байты сообщени€
        }
    }
}


void ServerConnectorTCP::ExecuteTasks()
{
    int64 now = GF::Timer::TimeMS();

    for (TaskMasterServer * task : all_tasks)
    {
        if (now >= task->prev_time + task->delta_time)
        {
            uint id = task->request();

            task->prev_time = now;

            if (task->handler_answer)
            {
                active_tasks[id] = task;
            }
        }
    }
}


void ServerConnectorTCP::SetTask(int64 dT, TaskMasterServer *task)
{
    task->delta_time = dT;

    task->last_tive_receive = LLONG_MAX;

    all_tasks.push_back(task);
}


bool ServerConnectorTCP::ExistConnection()
{
    int64 now = GF::Timer::TimeMS();

    if (active_tasks.size() == 0)
    {
        return true;
    }

    for (auto &it : active_tasks)
    {
        TaskMasterServer *task = it.second;

        if (now - task->last_tive_receive < 1500)
        {
            return true;
        }
    }

    return false;
}
