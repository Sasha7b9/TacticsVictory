// 2021/04/07 20:56:25 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Other/NetworkTypes_v.h"


std::string SockAddrIn::ToStringFull() const
{
    char buffer[100];

#ifdef WIN32
    sprintf_s(buffer, 100, "%d.%d.%d.%d:%d", addr.sin_addr.S_un.S_un_b.s_b1,
        addr.sin_addr.S_un.S_un_b.s_b2,
        addr.sin_addr.S_un.S_un_b.s_b3,
        addr.sin_addr.S_un.S_un_b.s_b4,
        addr.sin_port);
#else
    sprintf(buffer, "%d.%d.%d.%d:%d", (uint8)addr.sin_addr.s_addr,
        (uint8)(addr.sin_addr.s_addr >> 8),
        (uint8)(addr.sin_addr.s_addr >> 16),
        (uint8)(addr.sin_addr.s_addr >> 24),
        addr.sin_port);
#endif

    return std::string(buffer);
}


std::string ClientInfo::SocketAddress::ToStringHost() const
{
    char buffer[100];

    const sockaddr_in &_sin = sin.GetSockAddrInConst();

#ifdef WIN32
    sprintf_s(buffer, 100, "%d.%d.%d.%d", _sin.sin_addr.S_un.S_un_b.s_b1,
        _sin.sin_addr.S_un.S_un_b.s_b2,
        _sin.sin_addr.S_un.S_un_b.s_b3,
        _sin.sin_addr.S_un.S_un_b.s_b4);
#else
    sprintf(buffer, "%d.%d.%d.%d", (uint8)_sin.sin_addr.s_addr,
        (uint8)(_sin.sin_addr.s_addr >> 8),
        (uint8)(_sin.sin_addr.s_addr >> 16),
        (uint8)(_sin.sin_addr.s_addr >> 24));
#endif

    return std::string(buffer);
}


void SockAddrIn::SetHostIP(void *ip)
{
    addr = *((sockaddr_in *)ip);

#ifdef WIN32
    if (addr.sin_addr.S_un.S_un_b.s_b1 == 127 &&
        addr.sin_addr.S_un.S_un_b.s_b2 == 0 &&
        addr.sin_addr.S_un.S_un_b.s_b3 == 0 &&
        addr.sin_addr.S_un.S_un_b.s_b4 == 1)
    {
        system("ipconfig > address.txt");
    }
#else
    if ((uint8)(addr.sin_addr.s_addr >> 0) == 127 &&
        (uint8)(addr.sin_addr.s_addr >> 8) == 0 &&
        (uint8)(addr.sin_addr.s_addr >> 16) == 0 &&
        (uint8)(addr.sin_addr.s_addr >> 24) == 1)
    {
        [[maybe_unused]] auto result = system("wget -qO- eth0.me > address.txt");

        FS::File file;

        if (!file.Open("address.txt", __FILE__, __LINE__))
        {
            LOGERROR("Can not open file with address");
        }

        std::string ip;

        file.ReadString(ip);

        inet_aton(ip.c_str(), &addr.sin_addr);

        FS::RemoveFile("address.txt");
    }
#endif
}


uint ClientInfo::GetID(std::vector<uint8> &received)
{
    return *(uint *)received.data();
}


uint ClientInfo::GetSize(std::vector<uint8> &received)
{
    return *(uint *)(received.data() + 4);
}


void ClientInfo::MoveData(std::vector<uint8> &received, std::vector<uint8> &data)
{
    uint size = GetSize(received);

    data.resize(size);

    std::memcpy(data.data(), received.data() + 8, size);

    received.erase(received.begin(), received.begin() + 8 + size);
}


void *ClientInfo::GetRawData()
{
    char *string = (char *)message.data();

    if (std::strlen(string) + 1 == message.size())
    {
        return nullptr;
    }

    return message.data() + std::strlen(string) + 1;
}


bool TaskMasterServer::ExistCompleted(std::vector<TaskMasterServer *> &tasks)
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
    
#ifdef WIN32

    int result = InetPtonA(family, ip, &addr.sin_addr.S_un.S_addr);

    if (result != 1)
    {
        LOGERRORF("Error int function InetPtonA this ip-address %s", ip);
    }

#else
    addr.sin_addr.s_addr = inet_addr(ip);
#endif

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


char *SockAddrIn::GetIP()
{
    return inet_ntoa(addr.sin_addr);
}


uint16 SockAddrIn::GetPort()
{
    return addr.sin_port;
}


sockaddr *SockAddrIn::GetSockAddr()
{
    return (struct sockaddr *)&addr;
}
