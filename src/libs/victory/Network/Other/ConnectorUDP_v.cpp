// 2021/04/27 16:28:49 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Other/ConnectorUDP_v.h"


void ConnectorUDP::AcceptServer(pchar _ip, uint16 _port)
{
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

#ifdef WIN32
#pragma warning(push, 0)
#endif
    addr.sin_family = AF_INET;
    addr.sin_port = htons(_port);
#ifdef WIN32
    addr.sin_addr.S_un.S_addr = inet_addr(_ip);
#else
    addr.sin_addr.s_addr = inet_addr(_ip);
#endif
#ifdef WIN32
#pragma warning(pop)
#endif
}


void ConnectorUDP::SendMessage(pchar message)
{
    int num_bytes = sendto(sock_fd, message, (int)std::strlen(message), 0, (struct sockaddr *)&addr, sizeof(addr));

    LOGWRITEF("Sended %d bytes", num_bytes);
}
