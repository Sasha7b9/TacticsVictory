// 2021/04/27 16:29:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class ConnectorUDP
{
public:

    void AcceptServer(pchar ip, uint16 port);

    void SendMessage(pchar message);

private:

    SOCKET sock_fd = 0;
    struct sockaddr_in addr;
};
