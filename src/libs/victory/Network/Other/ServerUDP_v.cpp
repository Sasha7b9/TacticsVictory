// 2021/04/09 14:45:08 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "FileSystem/ConfigurationFile_v.h"
#include "FileSystem/FileSystem_v.h"
#include "Network/Other/NetworkTypes_v.h"
#include "Network/Other/ServerUDP_v.h"
#include "Utils/StringUtils_v.h"
#ifdef WIN32
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif


#define MAX_LINE 16384


void ServerUDP::Run(uint16 port)
{
    event_set_log_callback(CallbackLog);

#ifdef WIN32
    WSADATA wsa_data;
    if (WSAStartup(0x0201, &wsa_data) != 0)
    {
        LOGERROR("Can not execute WSAStartup(0x0201, &wsa_data)");
        return;
    };
#endif

    struct event_base *base = event_base_new();

    evutil_socket_t sock = (evutil_socket_t)socket(AF_INET, SOCK_DGRAM, 0);

    evutil_make_socket_nonblocking(sock);

#ifdef WIN32
#else
    {
        int one = 1;
        setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    }
#endif

    SockAddrIn sin;
    sin.Init(AF_INET, nullptr, port);

    if (sin.Bind(sock) >= 0)
    {
        LOGWRITEF("Bind to port %d for broadcast messages is Ok! Wait messages ...", port);
    }

    CallbackArgs args = { this, base };

    struct event *evnt = event_new(base, sock, EV_READ | EV_PERSIST, CallbackRead, &args);

    event_add(evnt, NULL);

    event_base_dispatch(base);
}


void ServerUDP::CallbackLog(int, const char *message)
{
    LOGERROR(message);
}


void ServerUDP::SendAnswer(void *bevnt, uint id, pchar message, void *data, uint size_data)
{
    bufferevent_write((struct bufferevent *)bevnt, &id, 4);

    uint full_size = (uint)std::strlen(message) + 1 + size_data;

    bufferevent_write((struct bufferevent *)bevnt, &full_size, 4);

    bufferevent_write((struct bufferevent *)bevnt, message, std::strlen(message) + 1);

    if (data)
    {
        bufferevent_write((struct bufferevent *)bevnt, data, size_data);
    }
}


void ServerUDP::SendAnswer(void *bevnt, uint id, pchar message, pchar data)
{
    SendAnswer(bevnt, id, message, (void *)data, (uint)std::strlen(data) + 1);
}


void ServerUDP::SendAnswer(void *bevnt, uint id, pchar message, int value)
{
    SendAnswer(bevnt, id, message, &value, sizeof(value));
}


void ServerUDP::CallbackRead(evutil_socket_t sock, short /*event*/, void *)
{
    char buf[1024] = "";

    SockAddrIn address;

    int size = address.RecvFrom(sock, buf, 1024);

    if (size > 0)
    {
        LOGWRITEF("From %s:%d : \"%s\"", address.GetIP(), address.GetPort(), buf);;
    }

//#ifdef WIN32
//    sendto((SOCKET)sock, buf, sizeof(buf), 0, (struct sockaddr *)&address.addr, size);
//#else
//    sendto(sock, buf, sizeof(buf), 0, (struct sockaddr *)&address.addr, size);
//#endif
}


void ServerUDP::ProcessClient(ClientInfo &info, ServerUDP *server)
{
    std::vector<uint8> &received = info.message.data;

    while (received.size() > sizeof(uint) * 2)         // ≈сли прин€то данных больше, чем занимают id и размер данных
    {
        uint id = ClientMessage::GetID(received);

        uint size = ClientMessage::GetSize(received);

        if (received.size() >= sizeof(uint) * 2 + size)
        {
            info.message.MoveRawFrom(received);

            SU::SplitToWords((char *)info.message.raw.data(), info.message.words);

            auto it = server->handlers.find(info.message.words[0]);

            if (it != server->handlers.end())
            {
                it->second(id, info);
            }
        }
        else
        {
            break;      // ≈сли прин€ты не все байты запроса
        }
    }
}


void ServerUDP::CallbackError(struct bufferevent *bevnt, short error, void *_args)
{
    ServerUDP *server = ((CallbackArgs *)_args)->server;

    if (error & BEV_EVENT_READING)
    {
        LOGWRITEF("Client %s disconnected", server->clients[bevnt].address.ToStringFull().c_str());

        server->clients.erase(bevnt);
    }
    else if (error & BEV_EVENT_WRITING)
    {
        LOGERROR("BEV_EVENT_WRITING");
    }
    else if (error & BEV_EVENT_EOF)
    {
        LOGERROR("BEV_EVENT_EOF");
    }
    else if (error & BEV_EVENT_TIMEOUT)
    {
        LOGERROR("BEV_EVENT_TIMEOUT");
    }
    else if (error & BEV_EVENT_CONNECTED)
    {
        LOGERROR("BEV_EVENT_TIMEOUT");
    }
    else
    {
        LOGERROR("Unknown error occured");
    }

    bufferevent_free(bevnt);
}


void ServerUDP::AppendHandler(pchar command, handlerClient handler)
{
    handlers[command] = handler;
}
