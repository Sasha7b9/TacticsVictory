// 2021/04/09 14:45:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Network/Other/NetworkTypes_v.h"
#include <map>
#ifdef WIN32
#include <WinSock2.h>
#endif


class ServerTCP
{
public:

    virtual ~ServerTCP() {}

    typedef void (*handlerClient) (uint, ClientInfo &);

    void Run(uint16 port);

    void Stop() { run = false; }

    void AppendHandler(pchar command, handlerClient handler);

    void SendAnswer(void *bevnt, uint id, pchar message, void *data = nullptr, uint size = 0);
    void SendAnswer(void *bevnt, uint id, pchar message, pchar data);
    void SendAnswer(void *bevnt, uint id, pchar message, int value);

    std::map<std::string, handlerClient> handlers;   // Здесь хранятся обработчики запросов по первому слову

private:

    bool run = true;

    struct CallbackArgs
    {
        ServerTCP  *server;
        event_base *base;
    };

    // Вызывается при новом соединении
    static void CallbackRead(struct bufferevent *, void *arg);
    static void CallbackWrite(struct bufferevent *, void *arg);
    static void CallbackAccept(evutil_socket_t listener, short event, void *arg);
    static void CallbackError(struct bufferevent *bevnt, short what, void *ctx);
    static void CallbackLog(int, const char *);

    static void ProcessClient(ClientInfo &info, ServerTCP *server);

    // Вызывается в CallbackAccept() при присоединении нового клиента
    virtual void HandlerOnAccepted(ClientInfo &info) = 0;

    // Вызываются в CallbackRead()
    virtual std::vector<uint8> &HandlerOnRead1(void *bevnt) = 0;
    virtual ClientInfo &HandlerOnRead2(void *bevnt) = 0;

    // Вызывается в CallbackError()
    virtual void HandlerOnError(void *bevnt) = 0;
};
