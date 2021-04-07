// 2021/04/07 20:56:25 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Other/NetworkTypes_.h"
#include <sstream>


void ServerInfo::AppendInfo(std::string address, std::string &buffer)
{
    std::stringstream ss;

    ss << address << ' ' << name << ' ' << std::rand() % 500 << ' ' << std::rand() % 100 << ':';

    buffer.append(ss.str());
}