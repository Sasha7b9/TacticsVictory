// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


void MasterServer::Connnect() //-V2506
{
    mutex.lock();
    destroy = false;

    pchar fullAddress = TheConfig.GetStringValue("address master");

    auto [host, port] = ConnectorTCP::ParseAddress(fullAddress);

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
