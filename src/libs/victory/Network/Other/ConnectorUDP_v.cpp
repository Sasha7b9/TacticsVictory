// 2021/04/27 16:28:49 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Other/ConnectorUDP_v.h"


void ConnectorUDP::AcceptServer(pchar _ip, uint16 _port)
{
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

    addr.Init(AF_INET, _ip, _port);
}


void ConnectorUDP::Send(pchar message)
{
    int need_bytes = (int)std::strlen(message) + 1;

    if (sendto(sock_fd, message, need_bytes, 0, addr.GetSockAddr(), sizeof(addr)) == -1)
    {
        LOGERRORF("Can not send to %s", addr.ToStringFull().c_str());
    }
}


void ConnectorUDP::SetTask(ServerTask *)
{

}
