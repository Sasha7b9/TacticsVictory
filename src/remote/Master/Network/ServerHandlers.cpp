// 2021/03/31 22:30:19 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "FileSystem/ConfigurationFile_.h"
#include "Network/Other/NetworkTypes_.h"
#include "Network/Other/Server_.h"
#include "Utils/StringUtils_.h"


static void HandleInfoLivingRoms(uint, ClientInfo &);
static void HandlerPing(uint, ClientInfo &);
static void HandlerSetNameLivingRoom(uint, ClientInfo &);



void Server::Prepare()
{
    AppendHandler(MSG_NTW_INFO_LIVINGROOM,     HandleInfoLivingRoms);
    AppendHandler(MSG_NTW_PING,                HandlerPing);
    AppendHandler(MSG_NTW_SET_NAME_LIVINGROOM, HandlerSetNameLivingRoom);
};


static void HandleInfoLivingRoms(uint id, ClientInfo &info)
{
    std::string result;

    std::stringstream stream(result);

    for each (auto &pair in TheServer.clients)
    {
        const ClientInfo &ci = pair.second;

        if (!ci.name.empty())
        {
            stream << ci.name << ',';
            stream << ci.address.ToString().c_str() << ',';
            stream << std::rand() << ',';
            stream << 123 << '|';
        }
    }

    TheServer.SendAnswer(info.benv, id, MSG_NTW_INFO_LIVINGROOM, stream.str().c_str());
}


static void HandlerPing(uint id, ClientInfo &info)
{
    TheServer.SendAnswer(info.benv, id, MSG_NTW_PING, info.GetRawData(), 4);
}


static void HandlerSetNameLivingRoom(uint, ClientInfo &info)
{
    char *name = (char *)info.GetRawData();

    info.name = name;

    LOGWRITEF("name connected livingroom is \"%s\"", name);
}