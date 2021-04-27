// 2021/04/27 16:28:49 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Other/ConnectorUDP_v.h"


void ConnectorUDP::AcceptServer(pchar _ip, uint16 _port)
{
    static sockpp::socket_initializer sock_init;

    ip = _ip;
    port = _port;

    address = sockpp::inet_address(ip, port);
}


void ConnectorUDP::SendMessage(pchar message)
{
    ssize_t num_bytes = sock.send_to(message, address);

    LOGWRITEF("Sending %d bytes from message %s", num_bytes, message);
}
