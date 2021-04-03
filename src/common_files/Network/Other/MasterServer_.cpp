// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Other/MasterServer_.h"


void MasterServer::Connect() //-V2506
{
    pchar full_address = TheConfig.GetStringValue("address master");

    Connect(full_address);
}


void MasterServer::Connect(pchar full_address)
{
    mutex.lock();
    destroy = false;

    auto [host, port] = ConnectorTCP::ParseAddress(full_address);

    while (!connector.Connect(host, port) && !destroy)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    connector.SetReadTimeOut(10000);
    mutex.unlock();
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
