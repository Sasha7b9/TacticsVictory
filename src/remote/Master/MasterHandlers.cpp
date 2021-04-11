// 2021/03/31 22:30:19 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "FileSystem/ConfigurationFile_.h"
#include "Network/Other/NetworkTypes_.h"
#include "Network/Other/Server_.h"
#include "Utils/StringUtils_.h"


static void HandlerPing(uint, ClientInfo &);


std::map<std::string, Server::handlerClient> Server::handlers;


void Server::Prepare()
{
    AppendHandler("ping", HandlerPing);
}


static void HandlerPing(uint id, ClientInfo &info)
{
    struct bufferevent *bev = (struct bufferevent *)info.benv;

    TheServer.SendAnswer(bev, id, MSM_PING, info.GetRawData(), 4);
}
