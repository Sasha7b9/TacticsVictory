// 2021/04/07 20:56:25 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Other/NetworkTypes_.h"
#include <sstream>


void ServerInfo::AppendInfo(std::string addr, std::string &buffer)
{
    std::stringstream ss;

    ss << addr << ' ' << name << ' ' << std::rand() % 500 << ' ' << std::rand() % 100 << ' ';

    buffer.append(ss.str());
}


void ServerInfo::ParseString(const std::string &data, std::vector<ServerInfo> &servers)
{
    while (data.size() > 1)
    {
        ServerInfo info;

        std::stringstream ss(data);

        ss >> info.address;

        ss >> info.name;

        ss >> info.ping;

        ss >> info.cpu;

        servers.push_back(info);
    }
}