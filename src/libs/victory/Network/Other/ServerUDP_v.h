// 2021/04/09 14:45:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include <map>
#ifdef WIN32
#include <WinSock2.h>
#endif


class ServerUDP
{
public:

    typedef void (*handlerClient) (uint, ClientInfo &);

    void Run(uint16 port);

    void Stop() { run = false; }

    void AppendHandler(pchar command, handlerClient handler);

    void SendAnswer(void *bevnt, uint id, pchar message, void *data = nullptr, uint size = 0);
    void SendAnswer(void *bevnt, uint id, pchar message, pchar data);
    void SendAnswer(void *bevnt, uint id, pchar message, int value);

    std::map<std::string, handlerClient> handlers;   // Здесь хранятся обработчики запросов по первому слову

    std::map<void *, ClientInfo> clients;

private:

    bool run = true;

    struct CallbackArgs
    {
        ServerUDP       *server;
        event_base      *base;
    };

    // Вызывается при новом соединении
    static void CallbackRead(evutil_socket_t listener, short event, void *arg);
    static void CallbackError(struct bufferevent *bevnt, short what, void *ctx);
    static void CallbackLog(int, const char *);

    static void ProcessClient(ClientInfo &info, ServerUDP *server);
};
