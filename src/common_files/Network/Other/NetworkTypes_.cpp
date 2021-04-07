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
    std::stringstream ss(data);

    while (!ss.eof())
    {
        ServerInfo info;

        ss >> info.address;

        ss >> info.name;

        ss >> info.ping;

        ss >> info.cpu;

        if (!info.name.empty() && !info.address.empty())
        {
            servers.push_back(info);
        }
    }
}