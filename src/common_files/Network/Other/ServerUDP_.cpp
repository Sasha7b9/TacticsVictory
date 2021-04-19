// 2021/04/18 23:26:50 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Other/ServerUDP_.h"

#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
#include <string.h>
#include <fcntl.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
#include <iostream>


SocketUtility &SocketUtility::GetInstance()
{
    static SocketUtility object;
    return object;
}


int SocketUtility::BindSocket(const SocketConfig &config)
{
    int sock_fd = InitSocket(config.type);

    if (sock_fd < 0)
    {
        return sock_fd;
    }

    struct sockaddr_in addr = { 0 };
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(config.ip.c_str());
    addr.sin_port = htons(config.port);

    if (bind(sock_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        LOGERRORF("Socket bind failed on %s:%d", config.ip.c_str(), config.port);
        return sock_fd;
    }

    if (config.type == TypeServer::TCP)
    {
        if (listen(sock_fd, config.backLog) < 0)
        {
            LOGERRORF("Socket listen failed on backlog %d", config.backLog);
            return -1;
        }
    }

#ifdef WIN32

    LOGWARNING("Not realized for Windows");

#else

    int flag = fcntl(sock_fd, F_GETFL, 0);

    if (flag < 0)
    {
        LOGERRORF("fcntl F_GETFL on socket %d failed", sock_fd);
        return -1;
    }

    if (fcntl(sock_fd, F_SETFL, flag | O_NONBLOCK) < 0)
    {
        LOGERRORF("fcntl F_SETFL non block on socket %d failed", sock_fd);
        return -1;
    }

#endif

    return sock_fd;
}


bool SocketUtility::CloseSocket(int &sock_fd)
{
    if (sock_fd > 0)
    {
#ifdef WIN32
        closesocket(sock_fd);
#else
        close(sock_fd);
#endif

        return true;
    }

    return false;
}


int SocketUtility::InitSocket(TypeServer::E type)
{
    int sock_fd = -1;

    switch (type)
    {
    case TypeServer::UDP:   sock_fd = socket(AF_INET, SOCK_DGRAM, 0);  break;

    case TypeServer::TCP:   sock_fd = socket(AF_INET, SOCK_STREAM, 0);  break;
    }

    if (sock_fd < 0)
    {
        LOGERROR("Socket fd create failed ");

        return sock_fd;
    }

    int on = 1;

    if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on)) < 0)
    {
        LOGERROR("Set socket to reuse failed");
        return -1;
    }
}
