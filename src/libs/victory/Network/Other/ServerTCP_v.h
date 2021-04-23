// 2021/04/09 14:45:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include <map>
#ifdef WIN32
#include <WinSock2.h>
#endif


class ServerTCP
{
public:

    typedef void (*handlerClient) (uint, ClientInfo &);

    void Run(uint16 port);

    void Stop() { run = false; }

    void AppendHandler(pchar command, handlerClient handler);

    void SendAnswer(void *bev, uint id, pchar message, void *data = nullptr, uint size = 0);
    void SendAnswer(void *bev, uint id, pchar message, pchar data);
    void SendAnswer(void *bev, uint id, pchar message, int value);

    std::map<std::string, handlerClient> handlers;   // Здесь хранятся обработчики запросов по первому слову

    std::map<void *, ClientInfo> clients;

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
    static void CallbackError(struct bufferevent *bev, short what, void *ctx);
    static void CallbackLog(int, const char *);

    static void ProcessClient(ClientInfo &info, ServerTCP *server);
};
