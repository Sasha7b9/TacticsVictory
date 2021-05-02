// 2021/04/09 14:45:08 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "FileSystem/ConfigurationFile_v.h"
#include "FileSystem/FileSystem_v.h"
#include "Network/Other/NetworkTypes_v.h"
#include "Network/Other/ServerTCP_v.h"
#include "Utils/StringUtils_v.h"
#ifdef WIN32
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif


#define MAX_LINE 16384


void ServerTCP::Run(uint16 port)
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

    evutil_socket_t listener = (evutil_socket_t)socket(AF_INET, SOCK_STREAM, 0);

    evutil_make_socket_nonblocking(listener);

#ifdef WIN32
#else
    {
        int one = 1;
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    }
#endif

    SockAddrIn sin;
    sin.Init(AF_INET, nullptr, port);

    if (sin.Bind(listener) >= 0)
    {
        LOGWRITEF("Bind to port %d is Ok! Wait connections ...", port);
    }

    if(listen((socket_t)listener, 100) < 0)
    {
        LOGERROR("Can not call listen()");
    }

    CallbackArgs args = { this, base };

    struct event *listener_event = event_new(base, listener, EV_READ | EV_PERSIST, CallbackAccept, &args);

    event_add(listener_event, NULL);

    event_base_dispatch(base);
}


void ServerTCP::CallbackLog(int, const char *message)
{
    LOGERROR(message);
}


void ServerTCP::CallbackAccept(evutil_socket_t listener, short, void *_args)
{
    CallbackArgs *args = (CallbackArgs *)_args;

    struct event_base *base = args->base;

    struct sockaddr_storage ss;
    socklen_t slen = sizeof(ss);

    int fd = (int)accept((socket_t)listener, (struct sockaddr *)&ss, &slen);

    sockaddr addr;
    socklen_t len = sizeof(addr);

    getsockname((socket_t)fd, &addr, &len);

    if (fd < 0)
    {
        LOGERROR("Error accepted");
    }
    else
    {
        evutil_make_socket_nonblocking(fd);
        struct bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
        bufferevent_setcb(bev, CallbackRead, CallbackWrite, CallbackError, args);
//        bufferevent_setwatermark(bev, EV_READ | EV_WRITE, 0, 2);
        bufferevent_enable(bev, EV_READ | EV_WRITE);

        ClientInfo info;
        info.address.SetHostIP(&ss);
        info.benv = bev;

        LOGWRITEF("Open connection from %s", info.address.ToStringFull().c_str());

//        args->server->clients[bev] = info;

        static uint id = 0;

        args->server->HandlerOnAccepted(++id, bev, info);
    }
}


void ServerTCP::SendAnswer(void *bev, uint id, pchar message, void *data, uint size_data)
{
    if (bufferevent_write((struct bufferevent *)bev, &id, 4) == -1)
    {
        LOGERROR("");
    }

    uint full_size = (uint)std::strlen(message) + 1 + size_data;

    if (bufferevent_write((struct bufferevent *)bev, &full_size, 4) == -1)
    {
        LOGERROR("");
    }

    if (bufferevent_write((struct bufferevent *)bev, message, std::strlen(message) + 1) == -1)
    {
        LOGERROR("");
    }

    if (data)
    {
        if (bufferevent_write((struct bufferevent *)bev, data, size_data) == -1)
        {
            LOGERROR("");
        }
    }
}


void ServerTCP::SendAnswer(void *bev, uint id, pchar message, pchar data)
{
    SendAnswer(bev, id, message, (void *)data, (uint)std::strlen(data) + 1);
}


void ServerTCP::SendAnswer(void *bev, uint id, pchar message, int value)
{
    SendAnswer(bev, id, message, &value, sizeof(value));
}


void ServerTCP::CallbackRead(struct bufferevent *bev, void *_args)
{
    CallbackArgs *args = (CallbackArgs *)_args;

    std::vector<uint8> &data = args->server->HandlerOnRead1(bev);

#define SIZE_CHUNK 1024

    uint8 buffer[SIZE_CHUNK];

    size_t readed = bufferevent_read(bev, buffer, SIZE_CHUNK);

    while (readed)
    {
        data.insert(data.end(), &buffer[0], &buffer[readed]);

        readed = bufferevent_read(bev, buffer, SIZE_CHUNK - 1);
    }

//    ProcessClient(args->server->clients[bev], args->server);

    ProcessClient(args->server->HandlerOnRead2(bev), args->server);
}


void ServerTCP::CallbackWrite(struct bufferevent *, void *)
{

}


void ServerTCP::ProcessClient(ClientInfo &info, ServerTCP *server)
{
    std::vector<uint8> &received = info.bindata;

    while (received.size() > 4 + 4)         // ≈сли прин€то данных больше, чем занимают id и размер данных
    {
        uint id = ClientInfo::GetID(received);

        uint size = ClientInfo::GetSize(received);

        if (received.size() >= 4 + 4 + size)
        {
            ClientInfo::MoveData(received, info.message);

            SU::SplitToWords((char *)info.message.data(), info.words);

            for (uint i = 0; i < info.words.size(); i++)
            {
                if (info.words[i] != "ping")
                {
//                    LOGWRITEF("received \"%s\"", info.words[i].c_str());
                }
            }

            auto it = server->handlers.find(info.words[0]);

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


void ServerTCP::CallbackError(struct bufferevent *bev, short error, void *_args)
{
    ServerTCP *server = ((CallbackArgs *)_args)->server;

    if (error & BEV_EVENT_READING)
    {
        server->HandlerOnError(bev);
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

    bufferevent_free(bev);
}


void ServerTCP::AppendHandler(pchar command, handlerClient handler)
{
    handlers[command] = handler;
}
