// 2021/05/02 11:16:48 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Server.h"


ClientServerInfo ClientServerInfo::empty;


ClientServerInfo::ClientServerInfo(const ClientInfo &rhs)
{
    address = rhs.address;
    benv = rhs.benv;
    message = rhs.message;
}


Server::Server() : ServerTCP()
{

}


void Server::HandlerOnAccepted(ClientInfo &info)
{
    clients[info.id] = info;
}


std::vector<uint8> &Server::HandlerOnRead1(void *bev)
{
    return GetClient(bev).message.data;
}


ClientInfo &Server::HandlerOnRead2(void *bev)
{
    return GetClient(bev);
}


void Server::HandlerOnError(void *bev)
{
    ClientServerInfo *client = &GetClient(bev);

    LOGWRITEF("Close connection from %s", client->address.ToStringFull().c_str());
    clients.erase(client->id);
}


void Server::AppendHandler(pchar command, handlerClient handler)
{
    ServerTCP::AppendHandler(command, (ServerTCP::handlerClient)handler);
}


ClientServerInfo &Server::GetClient(void *bev)
{
    for (auto &elem : clients)
    {
        ClientServerInfo &client = elem.second;

        if (client.benv == bev)
        {
            return client;
        }
    }

    return ClientServerInfo::empty;
}
