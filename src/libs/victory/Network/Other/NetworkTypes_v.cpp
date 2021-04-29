// 2021/04/07 20:56:25 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Other/NetworkTypes_v.h"


std::string ClientInfo::SocketAddress::ToStringFull() const
{
    char buffer[100];

#ifdef WIN32
    sprintf_s(buffer, 100, "%d.%d.%d.%d:%d", sin.sin_addr.S_un.S_un_b.s_b1,
        sin.sin_addr.S_un.S_un_b.s_b2,
        sin.sin_addr.S_un.S_un_b.s_b3,
        sin.sin_addr.S_un.S_un_b.s_b4,
        sin.sin_port);
#else
    sprintf(buffer, "%d.%d.%d.%d:%d", (uint8)sin.sin_addr.s_addr,
        (uint8)(sin.sin_addr.s_addr >> 8),
        (uint8)(sin.sin_addr.s_addr >> 16),
        (uint8)(sin.sin_addr.s_addr >> 24),
        sin.sin_port);
#endif

    return std::string(buffer);
}


std::string ClientInfo::SocketAddress::ToStringHost() const
{
    char buffer[100];

#ifdef WIN32
    sprintf_s(buffer, 100, "%d.%d.%d.%d", sin.sin_addr.S_un.S_un_b.s_b1,
        sin.sin_addr.S_un.S_un_b.s_b2,
        sin.sin_addr.S_un.S_un_b.s_b3,
        sin.sin_addr.S_un.S_un_b.s_b4);
#else
    sprintf(buffer, "%d.%d.%d.%d", (uint8)sin.sin_addr.s_addr,
        (uint8)(sin.sin_addr.s_addr >> 8),
        (uint8)(sin.sin_addr.s_addr >> 16),
        (uint8)(sin.sin_addr.s_addr >> 24));
#endif

    return std::string(buffer);
}


void ClientInfo::SocketAddress::SetHostIP(void *ip)
{
    sin = *((sockaddr_in *)ip);

#ifdef WIN32
    if (sin.sin_addr.S_un.S_un_b.s_b1 == 127 &&
        sin.sin_addr.S_un.S_un_b.s_b2 == 0 &&
        sin.sin_addr.S_un.S_un_b.s_b3 == 0 &&
        sin.sin_addr.S_un.S_un_b.s_b4 == 1)
    {
        system("ipconfig > address.txt");
    }
#else
    if ((uint8)(sin.sin_addr.s_addr >> 0) == 127 &&
        (uint8)(sin.sin_addr.s_addr >> 8) == 0 &&
        (uint8)(sin.sin_addr.s_addr >> 16) == 0 &&
        (uint8)(sin.sin_addr.s_addr >> 24) == 1)
    {
        [[maybe_unused]] auto result = system("wget -qO- eth0.me > address.txt");

        FS::File file;

        if (!file.Open("address.txt", __FILE__, __LINE__))
        {
            LOGERROR("Can not open file with address");
        }

        std::string ip;

        file.ReadString(ip);

        inet_aton(ip.c_str(), &sin.sin_addr);

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


sockaddr *SockAddrIn::GetAddr()
{
    addr.sin_family = sin_family;
    addr.sin_port = sin_port;

#ifdef WIN32
    addr.sin_addr.S_un.S_addr = sin_addr;
#else
    addr.sin_addr.s_addr = sin_addr;
#endif

    return (struct sockaddr *)&addr;
}
