// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Other/MasterServer_.h"


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
    connector.Transmit(key);

    return connector.ReceiveWait();
}


static void ThreadPing(ConnectorTCP *connector, std::mutex *mutex, int *ping, uint8 *state)
{
    mutex->lock();

    auto start = std::chrono::system_clock::now();

    connector->Transmit("ping");

    std::string result = connector->Receive();

    if (result == "ping")
    {
        *state = MasterServer::State::GetPing;

        auto end = std::chrono::system_clock::now();

        *ping = (int)std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
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
            state = State::WaitPing;
            std::thread thread(ThreadPing, &connector, &mutex, &ping, (uint8 *)&state);
            thread.detach();
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
