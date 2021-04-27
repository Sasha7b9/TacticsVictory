// 2021/04/27 16:28:49 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Other/ConnectorUDP_v.h"


void ConnectorUDP::AcceptServer(pchar _ip, uint16 _port)
{
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(_port);
    addr.sin_addr.S_un.S_addr = inet_addr(_ip);
}


void ConnectorUDP::SendMessage(pchar message)
{
    int num_bytes = sendto(sock_fd, message, std::strlen(message), 0, (struct sockaddr *)&addr, sizeof(addr));

    LOGWRITEF("Sended %d bytes", num_bytes);
}
