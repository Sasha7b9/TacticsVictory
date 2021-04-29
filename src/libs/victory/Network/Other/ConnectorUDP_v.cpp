// 2021/04/27 16:28:49 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Other/ConnectorUDP_v.h"


void ConnectorUDP::AcceptServer(pchar _ip, uint16 _port)
{
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

    addr.Init(AF_INET, _ip, _port);
}


void ConnectorUDP::SendMessage(pchar message)
{
    int need_bytes = (int)std::strlen(message) + 1;

    int sending_bytes = sendto(sock_fd, message, need_bytes, 0, addr.GetSockAddr(), sizeof(addr));

    if (need_bytes == sending_bytes)
    {
        LOGWRITEF("Send message \"%s\"", message);
    }
    else
    {
        LOGERROR("Can not send message");
    }
}
