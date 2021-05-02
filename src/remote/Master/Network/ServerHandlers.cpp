// 2021/03/31 22:30:19 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "FileSystem/ConfigurationFile_v.h"
#include "Network/Server.h"
#include "Network/Other/NetworkTypes_v.h"
#include "Utils/StringUtils_v.h"
#include <sstream>


static void HandleInfoLivingRoms(uint, ClientServerInfo &);
static void HandlerPing(uint, ClientServerInfo &);
static void HandlerSetNameLivingRoom(uint, ClientServerInfo &);
static void HandlerGet(uint, ClientServerInfo &);



void PrepareServerTCP()
{
    TheServer.AppendHandler(MSG_NTW_INFO_LIVINGROOM,     HandleInfoLivingRoms);
    TheServer.AppendHandler(MSG_NTW_PING,                HandlerPing);
    TheServer.AppendHandler(MSG_NTW_SET_NAME_LIVINGROOM, HandlerSetNameLivingRoom);
    TheServer.AppendHandler(MSG_NTW_GET,                 HandlerGet);
};


static void HandleInfoLivingRoms(uint id, ClientServerInfo &info)
{
    std::string result;

    std::stringstream stream(result);

    for (auto &pair : TheServer.clients)
    {
        const ClientServerInfo &ci = pair.second;

        if (ci.IsLivingRoom())
        {
            stream << ci.name << ',';
            stream << ci.address.ToStringFull().c_str() << ',';
            stream << (std::rand() % 1000) << ',';
            stream << 123 << '|';
        }
    }

    TheServer.SendAnswer(info.bevnt, id, MSG_NTW_INFO_LIVINGROOM, stream.str().c_str());
}


static void HandlerPing(uint id, ClientServerInfo &info)
{
    TheServer.SendAnswer(info.bevnt, id, MSG_NTW_PING, info.message.GetRawData(), 4);
}


static void HandlerSetNameLivingRoom(uint, ClientServerInfo &info)
{
    char *name = (char *)info.message.GetRawData();

    info.name = name;
}


static void HandlerGet(uint id, ClientServerInfo &info)
{
    std::vector<std::string> &words = info.message.words;

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

                        TheServer.SendAnswer(info.bevnt, id, MSG_NTW_GET_PORT_LIVINGROOM_BROADCAST_UDP, delta);
                    }
                }
            }
        }
    }
}
