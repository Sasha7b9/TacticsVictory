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

    if (address.empty())
    {
        LOGERRORF("Not specified address master server");

        return;
    }

    std::thread thread(ThreadConnect, &connector, address.c_str(), &mutex);

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
