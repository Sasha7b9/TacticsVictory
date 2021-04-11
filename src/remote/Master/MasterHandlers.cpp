// 2021/03/31 22:30:19 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "FileSystem/ConfigurationFile_.h"
#include "Network/Other/NetworkTypes_.h"
#include "Network/Other/Server_.h"
#include "Utils/StringUtils_.h"


static void HandlerClose(uint, ClientInfo &);
static void HandlerGet(uint, ClientInfo &);
static void HandlerPing(uint, ClientInfo &);
extern void HandlerTerminate(uint, ClientInfo &);


std::map<std::string, handlerClient> Server::handlers;


void Server::Prepare()
{
    AppendHandler("close", HandlerClose);
    AppendHandler("get", HandlerGet);
    AppendHandler("ping", HandlerPing);
    AppendHandler("terminate", HandlerTerminate);
}


static void HandlerClose(uint, ClientInfo &info)
{
    if (info.words.size() == 2 && (info.words)[1] == "connection")
    {
//        sock->sock.close();
    }
}


static void HandlerGet(uint, ClientInfo &)
{
//    if (words->size() == 2)
//    {
//        if ((*words)[1] == "livingrooms")
//        {
//            std::string data;
//
//            auto room = Server::infos.begin();
//
//            while (room != Server::infos.end())
//            {
//                room->second.AppendInfo(room->first, data);
//
//                room++;
//            }
//
////            sock->Transmit(data);
//        }
//    }
//    else if (words->size() == 3)
//    {
//        if ((*words)[1] == "address")                                                          // get address
//        {
//            pchar address = TheConfig.GetString("address", (*words)[2].c_str());
//            if (address)
//            {
////                sock->Transmit(address);
//            }
//            else
//            {
//                LOGERRORF("Invalid request : \"%s %s %s\"",
//                    (*words)[0].c_str(), (*words)[1].c_str(), (*words)[2].c_str());
//            }
//        }
//    }
}


static void HandlerPing(uint id, ClientInfo &info)
{
    LOGWRITE("Request for ping");

    struct bufferevent *bev = (struct bufferevent *)info.benv;

    TheServer.SendAnswer(bev, id, MSM_PING);
}


void HandlerTerminate(uint, ClientInfo &)
{
    TheServer.Stop();
}
