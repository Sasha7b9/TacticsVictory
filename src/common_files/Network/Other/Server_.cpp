// 2021/04/09 14:45:08 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "FileSystem/ConfigurationFile_.h"
#include "Network/Other/NetworkTypes_.h"
#include "Network/Other/Server_.h"


static const char MESSAGE[] = "Hello, World!";

// Вызывается при новом соединении
static void CallbackRead(struct bufferevent *, void *);
static void CallbackAccept(evutil_socket_t listener, short event, void *arg);
static void CallbackError(struct bufferevent *bev, short what, void *ctx);
static void SendString(void *bufevnt, pchar message);
static void CallbackLog(int, const char *);


#define MAX_LINE 16384


struct SocketAddress
{
    std::string ToString()
    {
        char buffer[100];

        sprintf_s(buffer, 100, "%d.%d.%d.%d:%d", sin.sin_addr.S_un.S_un_b.s_b1,
            sin.sin_addr.S_un.S_un_b.s_b2,
            sin.sin_addr.S_un.S_un_b.s_b3,
            sin.sin_addr.S_un.S_un_b.s_b4,
            sin.sin_port);

        return std::string(buffer);
    };

    sockaddr_in sin;
};


struct ClientInfo
{
    SocketAddress address;
    std::vector<uint8> data;
};

std::map<void *, ClientInfo> clients;


static void ProcessClient(ClientInfo &info);


void Server::Run()
{
    event_set_log_callback(CallbackLog);

    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(40000);

#ifdef WIN32
    WSADATA wsa_data;
    WSAStartup(0x0201, &wsa_data);
#endif

    struct event_base *base = event_base_new();

    evutil_socket_t listener = (evutil_socket_t)socket(AF_INET, SOCK_STREAM, 0);

    evutil_make_socket_nonblocking(listener);

#ifndef WIN32
    {
        int one = 1;
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    }
#endif

    if (bind((SOCKET)listener, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        LOGERROR("Can not bind to port");
    }

    if (listen((SOCKET)listener, 100) < 0)
    {
        LOGERROR("Can not call listen()");
    }

    struct event *listener_event = event_new(base, listener, EV_READ | EV_PERSIST, CallbackAccept, (void *)base);

    event_add(listener_event, NULL);

    event_base_dispatch(base);
}


static void CallbackLog(int, const char *message)
{
    LOGERROR(message);
}


static void CallbackAccept(evutil_socket_t listener, short, void *arg)
{
    struct event_base *base = (struct event_base *)arg;

    struct sockaddr_storage ss;
    socklen_t slen = sizeof(ss);

    int fd = (int)accept((SOCKET)listener, (struct sockaddr *)&ss, &slen);

    if (fd < 0)
    {
        LOGERROR("Error accepted");
    }
    else
    {
        evutil_make_socket_nonblocking(fd);
        struct bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
        bufferevent_setcb(bev, CallbackRead, NULL, CallbackError, NULL);
        bufferevent_setwatermark(bev, EV_READ, 0, MAX_LINE);
        bufferevent_enable(bev, EV_READ | EV_WRITE);

        ClientInfo info;
        info.address.sin = *((sockaddr_in *)&ss);

        LOGWRITEF("Client %s connected", info.address.ToString().c_str());

        clients[bev] = info;
    }
}


//static void SendString(void *bufevnt, pchar message)
//{
//    uint size = (uint)std::strlen(message);
//
//    bufferevent_write((bufferevent *)bufevnt, &size, 4);
//
//    bufferevent_write((bufferevent *)bufevnt, message, size);
//}


static void CallbackRead(struct bufferevent *bev, void *)
{
    std::vector<uint8> &data = clients[bev].data;

#define SIZE_CHUNK 1024

    uint8 buffer[SIZE_CHUNK];

    size_t readed = bufferevent_read(bev, buffer, SIZE_CHUNK);

    while (readed)
    {
        data.insert(data.end(), &buffer[0], &buffer[readed]);

        readed = bufferevent_read(bev, buffer, SIZE_CHUNK);
    }

    ProcessClient(clients[bev]);
}


static void ProcessClient(ClientInfo &info)
{
    std::vector<uint8> &data = info.data;

    while (data.size() > 4)
    {
        uint size = *(uint *)data.data();

        if (data.size() >= 4 + size)
        {
            std::vector<char> buffer(size + 1);

            std::memcpy(buffer.data(), data.data() + 4, size);
            buffer[size] = '\0';

            LOGWRITEF("Received \"%s\" from %s", buffer.data(), info.address.ToString().c_str());

            data.erase(data.begin(), data.begin() + 4 + size);
        }
    }
}


static void CallbackError(struct bufferevent *bev, short error, void *)
{
    if (error & BEV_EVENT_READING)
    {
        LOGWRITEF("Client %s disconnected", clients[bev].address.ToString().c_str());

        clients.erase(bev);
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


void Server::AppendHandler(pchar command, pFuncVV handler)
{
    handlers[command] = handler;
}
