// 2021/05/02 11:16:48 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Server.h"


ClientServerInfo::ClientServerInfo(const ClientInfo &rhs)
{
    address = rhs.address;
    bindata = rhs.bindata;
    benv = rhs.benv;
    message = rhs.message;
    words = rhs.words;
}


Server::Server() : ServerTCP()
{

}


void Server::HandlerOnAccepted(uint , void *bev, ClientInfo info)
{
    clients[bev] = info;
}


std::vector<uint8> &Server::HandlerOnRead1(void *bev)
{
    return clients[bev].bindata;
}


ClientInfo &Server::HandlerOnRead2(void *bev)
{
    return clients[bev];
}


void Server::HandlerOnError(void *bev)
{
    LOGWRITEF("Close connection from %s", clients[bev].address.ToStringFull().c_str());
    clients.erase(bev);
}


void Server::AppendHandler(pchar command, handlerClient handler)
{
    ServerTCP::AppendHandler(command, (ServerTCP::handlerClient)handler);
}
