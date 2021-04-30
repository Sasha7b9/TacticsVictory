// 2021/04/27 16:29:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Network/Other/NetworkTypes_v.h"
#include <sockpp/platform.h>


class ConnectorUDP
{
public:

    void AcceptServer(pchar ip, uint16 port);

    void SendMessage(pchar message);

private:

    socket_t sock_fd = 0;

    SockAddrIn addr;
};
