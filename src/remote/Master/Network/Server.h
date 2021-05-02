// 2021/05/02 11:16:35 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Network/Other/ServerTCP_v.h"


struct ServerClientInfo : public ClientInfo
{
    ServerClientInfo() {}
    ServerClientInfo(const ClientInfo &);
};


class Server : public ServerTCP
{
public:

    Server();

    virtual ~Server() {};

    std::map<void *, ServerClientInfo> clients;

private:

    virtual void HandlerOnAccepted(uint id, void *bev, ClientInfo info) override;
    virtual std::vector<uint8> &HandlerOnRead1(void *bev) override;
    virtual ClientInfo &HandlerOnRead2(void *bev) override;
    virtual void HandlerOnError(void *bev) override;
};
