// 2021/04/07 20:56:25 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Other/NetworkTypes_v.h"
#include "Utils/GlobalFunctions_.h"


std::string SockAddrIn::ToStringFull() const
{
    return ToStringHost() + ":" + GF::IntToString(addr.sin_port, 0);
}


std::string SockAddrIn::ToStringHost() const
{
    char buffer[100];

#ifdef WIN32
    sprintf_s(buffer, 100, "%d.%d.%d.%d", addr.sin_addr.S_un.S_un_b.s_b1,
        addr.sin_addr.S_un.S_un_b.s_b2,
        addr.sin_addr.S_un.S_un_b.s_b3,
        addr.sin_addr.S_un.S_un_b.s_b4);
#else
    sprintf(buffer, "%d.%d.%d.%d", (uint8)addr.sin_addr.s_addr,
        (uint8)(addr.sin_addr.s_addr >> 8),
        (uint8)(addr.sin_addr.s_addr >> 16),
        (uint8)(addr.sin_addr.s_addr >> 24));
#endif

    return std::string(buffer);
}


void SockAddrIn::SetHostIP(void *ip)
{
    addr = *((sockaddr_in *)ip);
}


uint ClientMessage::GetID(std::vector<uint8> &received)
{
    return *(uint *)received.data();
}


uint ClientMessage::GetSize(std::vector<uint8> &received)
{
    return *(uint *)(received.data() + 4);
}


void ClientMessage::MoveData(std::vector<uint8> &received, std::vector<uint8> &data)
{
    uint size = GetSize(received);

    data.resize(size);

    std::memcpy(data.data(), received.data() + 8, size);

    received.erase(received.begin(), received.begin() + 8 + size);
}


void *ClientMessage::GetRawData()
{
    char *string = (char *)raw.data();

    if (std::strlen(string) + 1 == raw.size())
    {
        return nullptr;
    }

    return raw.data() + std::strlen(string) + 1;
}


bool ServerTask::ExistCompleted(std::vector<ServerTask *> &tasks)
{
    for (auto task : tasks)
    {
        if (task->counter == 0)
        {
            return true;
        }
    }

    return false;
}


void SockAddrIn::Init(uint16 family, pchar ip, uint16 port)
{
    addr.sin_family = family;
    addr.sin_port = htons(port);

    if (ip != nullptr)
    {
        int result = inet_pton(family, ip, &addr.sin_addr);

        if (result != 1)
        {
            LOGERRORF("Error int function inet_pton() this ip-address %s", ip);
        }
    }
}


pchar SockAddrIn::GetIP()
{
    const int SIZE_BUFFER = 100;

    static char buffer[SIZE_BUFFER];

    pchar result = inet_ntop(addr.sin_family, &addr.sin_addr, buffer, SIZE_BUFFER);

    if (result == nullptr)
    {
        LOGERROR("Error in inet_ntop()");
    }

    return result;
}


int SockAddrIn::RecvFrom(evutil_socket_t socket, char *buffer, int size_buffer)
{
    socklen_t size = sizeof(struct sockaddr);

    int received = recvfrom((socket_t)socket, buffer, size_buffer, 0, GetSockAddr(), &size);

    if (received < 0)
    {
        LOGERROR("Server recv message error");
    }
    else if (received == 0)
    {
        LOGERROR("Connetioin closed");
    }

    return received;
}


int SockAddrIn::Bind(evutil_socket_t socket)
{
    int result = bind((socket_t)socket, GetSockAddr(), sizeof(struct sockaddr));

    if (result < 0)
    {
        LOGERROR("Can not bind to port");
    }

    return result;
}


uint16 SockAddrIn::GetPort()
{
    return addr.sin_port;
}


sockaddr *SockAddrIn::GetSockAddr()
{
    return (struct sockaddr *)&addr;
}
