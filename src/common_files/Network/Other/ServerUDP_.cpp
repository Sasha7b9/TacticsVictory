// 2021/04/18 23:26:50 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Other/ServerUDP_.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <functional>
#include <iostream>


/// \todo Избавиться от предупреждений

#ifdef WIN32
#pragma warning(push)
#pragma warning(disable:4244 4365 4996)
#endif


class ThreadUDP
{
public:

    virtual ~ThreadUDP()
    {
        if (base != nullptr)
        {
            event_base_loopexit(base, NULL);
            event_base_free(base);
            base = nullptr;
        }

        if (ev != nullptr)
        {
            event_free(ev);
            ev = nullptr;
        }
    }

    bool Init(int fd)
    {
        if (fd < 0)
        {
            return false;
        }

        sock_fd = fd;
        base = event_base_new();

        if (nullptr == base)
        {
            return false;
        }

        ev = event_new(base, sock_fd, EV_READ | EV_PERSIST, ThreadUDP::CallbackReadUDP, this);

        if (nullptr == ev)
        {
            return false;
        }

        return 0 == event_add(ev, NULL);
    }

    void DispatchEventUDP()
    {
        if (base != nullptr)
        {
            event_base_dispatch(base);
        }
    }

    virtual bool DealMessageUDP(int fd) = 0;

#ifdef WIN32
    static void CallbackReadUDP(intptr_t fd, int16, void *arg)
#else
    static void CallbackReadUDP(int fd, int16, void *arg)
#endif
    {
        ThreadUDP *p = reinterpret_cast<ThreadUDP *>(arg);

        if (nullptr == p)
        {
            return;
        }

        p->DealMessageUDP(fd);
    }

protected:

    int sock_fd = -1;
    event_base *base = nullptr;
    event *ev = nullptr;
    static const int buffer_size = 1024;
};


class ThreadForTransactionUDP : public ThreadUDP
{
public:
    ThreadForTransactionUDP() = default;
    virtual ~ThreadForTransactionUDP() = default;

    virtual bool DealMessageUDP(int fd) override
    {
        char buf[buffer_size] = "";
        socklen_t size = sizeof(struct sockaddr);

        struct sockaddr_in client_addr;
        client_addr.sin_family = 0;

        int len = recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr, &size);

        if (len < 0)
        {
            LOGERROR("Server recv() message error");
            return false;
        }

        if (len == 0)
        {
            LOGERROR("Connection closed");
        }

        LOGWRITEF("Connection port %d", client_addr.sin_port);
        LOGWRITEF("Connection IP %s", inet_ntoa(client_addr.sin_addr));
        LOGWRITEF("Server recv() message len %d", len);
        LOGWRITE("Server send back message now");
        sendto(fd, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr, size);
        return true;
    }
};


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

    struct sockaddr_in addr;
    addr.sin_family = 0;

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

    if (setsockopt(sock_fd, SOL_SOCKET, SO_KEEPALIVE, (char *)&on, sizeof(on)) < 0)
    {
        LOGERROR("Set socket to keep alive failed");
        return -1;
    }

    return sock_fd;
}


ServerUDP::ServerUDP() : sock_fd(-1)
{

}


ServerUDP::~ServerUDP()
{
    for (auto &it : threads)
    {
        if (it.joinable())
        {
            it.join();
        }
    }

    SocketUtility::GetInstance().CloseSocket(sock_fd);
}


bool ServerUDP::Init(const SocketConfig &_config, int network_size)
{
    config = _config;

    Prepare();

    if (network_size <= 0 || network_size > network_capacity)
    {
        return false;
    }

    sock_fd = SocketUtility::GetInstance().BindSocket(config);

    if (sock_fd < 0)
    {
        return false;
    }

    threads.resize(network_size);

    for (int i = 0; i < network_size; i++)
    {
        threadsUPD.emplace_back(std::unique_ptr<ThreadUDP>(new ThreadForTransactionUDP()));

        if (!threadsUPD[i]->Init(sock_fd))
        {
            LOGERROR("UDP thread init failed");
            continue;
        }

        try
        {
            threads[i] = std::thread(std::bind(&ServerUDP::StartThreadUDP, this, i));
        }
        catch (const std::exception &ex)
        {
            LOGERRORF(ex.what());
            return false;
        }
    }

    return true;
}


void ServerUDP::StartThreadUDP(int index)
{
    threadsUPD[index]->DispatchEventUDP();
}


#ifdef WIN32
#pragma warning(pop)
#endif
