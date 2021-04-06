// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Other/MasterServer_.h"


static void ThreadConnect(ConnectorTCP *connector, pchar full_address, std::mutex *mutex)
{
    mutex->lock();

    auto [host, port] = ConnectorTCP::ParseAddress(full_address);

    if (connector->Connect(host, port))
    {
        connector->SetReadTimeOut(10000);
    }

    mutex->unlock();
}


void MasterServer::Connect()
{
    if (destroy)
    {
        return;
    }

    if (mutex.try_lock())
    {
        mutex.unlock();
    }
    else
    {
        return;
    }

    if (address.empty())
    {
        LOGERRORF("Not specified address master server");

        return;
    }

    std::thread thread(ThreadConnect, &connector, std::move(address.c_str()), &mutex);

    thread.detach();
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
