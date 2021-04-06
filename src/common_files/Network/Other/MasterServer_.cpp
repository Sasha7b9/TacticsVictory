// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Other/MasterServer_.h"


static void ThreadConnect(ConnectorTCP &connector, pchar full_address, bool &destroy, pFuncVV callback,
    std::mutex &mutex)
{
    mutex.lock();

    destroy = false;

    auto [host, port] = ConnectorTCP::ParseAddress(full_address);

    if (connector.Connect(host, port))
    {
        connector.SetReadTimeOut(10000);
    }

    mutex.unlock();

    callback();
}

void MasterServer::Connect(pchar full_address)
{
    if (callback == nullptr)
    {
        LOGERRORF("Callback for connection not set");
        return;
    }

    std::thread thread(ThreadConnect, connector, full_address, destroy, callback, mutex);

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

    mutex.lock();
    mutex.unlock();

    connector.Release();
}
