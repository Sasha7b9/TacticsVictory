// 2021/04/07 20:56:25 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Other/NetworkTypes_.h"
#include <sstream>


void ServerInfo::AppendInfo(std::string address, std::string &buffer)
{
    std::stringstream ss;

    if (!buffer.empty())
    {
        ss << ' ';
    }

    ss << address << ' ' << name << ' ' << ping << ' ' << cpu << '\x0d';

    buffer.append(ss.str());
}