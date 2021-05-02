// 2021/05/02 11:16:35 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Network/Other/ServerTCP_v.h"


struct ClientServerInfo : public ClientInfo
{
    ClientServerInfo() {}
    ClientServerInfo(const ClientInfo &);

    bool IsLivingRoom() const { return !name.empty(); }

    std::string     name;      // Имя гостиной, как оно будет отображаться в окне выбора сервера у игроков
};


class Server : public ServerTCP
{
public:

    typedef void (*handlerClient) (uint, ClientServerInfo &);

    Server();

    virtual ~Server() {};

    std::map<void *, ClientServerInfo> clients;

    void AppendHandler(pchar command, handlerClient handler);

private:

    virtual void HandlerOnAccepted(uint id, void *bev, ClientInfo info) override;
    virtual std::vector<uint8> &HandlerOnRead1(void *bev) override;
    virtual ClientInfo &HandlerOnRead2(void *bev) override;
    virtual void HandlerOnError(void *bev) override;
};
