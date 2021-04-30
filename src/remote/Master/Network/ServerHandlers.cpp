// 2021/03/31 22:30:19 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "FileSystem/ConfigurationFile_v.h"
#include "Network/Other/NetworkTypes_v.h"
#include "Network/Other/ServerTCP_v.h"
#include "Utils/StringUtils_v.h"
#include <sstream>


static void HandleInfoLivingRoms(uint, ClientInfo &);
static void HandlerPing(uint, ClientInfo &);
static void HandlerSetNameLivingRoom(uint, ClientInfo &);
static void HandlerGet(uint, ClientInfo &);



void PrepareServerTCP()
{
    TheServer.AppendHandler(MSG_NTW_INFO_LIVINGROOM,     HandleInfoLivingRoms);
    TheServer.AppendHandler(MSG_NTW_PING,                HandlerPing);
    TheServer.AppendHandler(MSG_NTW_SET_NAME_LIVINGROOM, HandlerSetNameLivingRoom);
    TheServer.AppendHandler(MSG_NTW_GET,                 HandlerGet);
};


static void HandleInfoLivingRoms(uint id, ClientInfo &info)
{
    std::string result;

    std::stringstream stream(result);

    for (auto &pair : TheServer.clients)
    {
        const ClientInfo &ci = pair.second;

        if (!ci.name.empty())
        {
            stream << ci.name << ',';
            stream << ci.address.ToStringHost().c_str() << ',';
            stream << (std::rand() % 1000) << ',';
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
}


static void HandlerGet(uint id, ClientInfo &info)
{
    std::vector<std::string> &words = info.words;

    if (words.size() > 0)
    {
        if (words[0] == MSG_NTW_GET)
        {
            if (words.size() > 2)
            {
                if (words[1] == "port")
                {
                    if (words[2] == "livingroom_broadcast_udp")
                    {
                        int delta = TheConfig.GetInt(words[1].c_str(), words[2].c_str());

                        TheServer.SendAnswer(info.benv, id, MSG_NTW_GET_PORT_LIVINGROOM_BROADCAST_UDP, delta);
                    }
                }
            }
        }
    }
}
