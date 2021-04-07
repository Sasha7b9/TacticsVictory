// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Other/MasterServer_.h"


static void ThreadConnect(ConnectorTCP *connector, pchar full_address, std::mutex *mutex,
    uint8 *state)
{
    mutex->lock();

    auto [host, port] = ConnectorTCP::ParseAddress(full_address);

    if (connector->Connect(host, port))
    {
        *state = MasterServer::State::InConnection;
        connector->SetReadTimeOut(10000);
    }
    else
    {
        *state = MasterServer::State::Idle;
    }

    mutex->unlock();
}


std::string MasterServer::GetValue(pchar key)
{
    connector.Transmit(key);

    return connector.ReceiveWait();
}


void MasterServer::Destroy()
{
    destroy = true;

    mutex.lock();           // Ожидаем завершения ThreadConnect
    mutex.unlock();

    connector.Release();
}


bool MasterServer::IsConnected()
{
    if (mutex.try_lock())
    {
        mutex.unlock();
        
        return connector.IsConnected();
    }

    return false;
}


void MasterServer::SetCallbacks(pFuncVV fail, pFuncVV connection, pFuncVV disconnection)
{
    funcFailConnection = fail;
    funcConnection = connection;
    funcDisconnection = disconnection;
}


void MasterServer::Connect()
{
    if (!funcFailConnection || !funcConnection || !funcDisconnection)
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


void MasterServer::Update()
{
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
                    std::thread thread(ThreadConnect, &connector, std::move(address.c_str()), &mutex, (uint8*)&state);
                    thread.detach();
                }
            }
        }
        break;

    case State::AttemptConnection:
        break;

    case State::InConnection:
        break;

    case State::WaitPing:
        break;
    }


//    if (TheMasterServer.IsConnected())
//    {
//        TheGUI->AppendInfo("Connection to master server established");
//    }
//    else
//    {
//        if (TheMasterServer.GetAddress()[0])
//        {
//            TheGUI->AppendWarning("Can't connect to master server");
//
//            TheMasterServer.Connect();
//        }
//    }
}
