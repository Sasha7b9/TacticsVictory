// 2021/04/09 14:45:08 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "FileSystem/ConfigurationFile_.h"
#include "Network/Other/NetworkTypes_.h"
#include "Network/Other/Server_.h"
#include "Utils/StringUtils_.h"


static const char MESSAGE[] = "Hello, World!";

// Вызывается при новом соединении
static void CallbackRead(struct bufferevent *, void *);
static void CallbackWrite(struct bufferevent *, void *);
static void CallbackAccept(evutil_socket_t listener, short event, void *arg);
static void CallbackError(struct bufferevent *bev, short what, void *ctx);
static void CallbackLog(int, const char *);


#define MAX_LINE 16384


std::map<void *, ClientInfo> clients;


static void ProcessClient(ClientInfo &info);


std::string ClientInfo::SocketAddress::ToString() const
{
    char buffer[100];

    sprintf_s(buffer, 100, "%d.%d.%d.%d:%d", sin.sin_addr.S_un.S_un_b.s_b1,
        sin.sin_addr.S_un.S_un_b.s_b2,
        sin.sin_addr.S_un.S_un_b.s_b3,
        sin.sin_addr.S_un.S_un_b.s_b4,
        sin.sin_port);

    return std::string(buffer);
}


void Server::Run()
{
    event_set_log_callback(CallbackLog);

    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(40000);

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
        bufferevent_setcb(bev, CallbackRead, CallbackWrite, CallbackError, NULL);
//        bufferevent_setwatermark(bev, EV_READ | EV_WRITE, 0, 2);
        bufferevent_enable(bev, EV_READ | EV_WRITE);

        ClientInfo info;
        info.address.sin = *((sockaddr_in *)&ss);
        info.benv = bev;

        LOGWRITEF("Client %s connected", info.address.ToString().c_str());

        clients[bev] = info;
    }
}


void Server::SendAnswer(void *bev, uint id, pchar message, void *data, uint size_data)
{
    bufferevent_write((struct bufferevent *)bev, &id, 4);

    uint full_size = (uint)std::strlen(message) + 1 + size_data;

    bufferevent_write((struct bufferevent *)bev, &full_size, 4);

    bufferevent_write((struct bufferevent *)bev, message, std::strlen(message) + 1);

    if (data)
    {
        bufferevent_write((struct bufferevent *)bev, data, size_data);
    }
}


static void CallbackRead(struct bufferevent *bev, void *)
{
    std::vector<uint8> &data = clients[bev].bindata;

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


static void CallbackWrite(struct bufferevent *, void *)
{
}


static uint GetID(std::vector<uint8> &received)
{
    return *(uint *)received.data();
}


static uint GetSize(std::vector<uint8> &received)
{
    return *(uint *)(received.data() + 4);
}


// Перемещает байты запроса из received в data. При этом из искоходного вектора перемещённые данные удаляются
static void MoveData(std::vector<uint8> &received, std::vector<uint8> &data)
{
    uint size = GetSize(received);

    data.resize(size);

    std::memcpy(data.data(), received.data() + 8, size);

    received.erase(received.begin(), received.begin() + 8 + size);
}


static void ProcessClient(ClientInfo &info)
{
    std::vector<uint8> &received = info.bindata;

    while (received.size() > 4 + 4)         // Если принято данных больше, чем занимают id и размер данных
    {
        uint id = GetID(received);

        uint size = GetSize(received);

        if (received.size() >= 4 + 4 + size)
        {
            MoveData(received, info.message);

            SU::SplitToWords((char *)info.message.data(), info.words);

            auto it = Server::handlers.find(info.words[0]);

            if (it != Server::handlers.end())
            {
                it->second(id, info);
            }
        }
        else
        {
            break;      // Если приняты не все байты запроса
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


void Server::AppendHandler(pchar command, handlerClient handler)
{
    handlers[command] = handler;
}


void *ClientInfo::GetRawData()
{
    char *string = (char *)message.data();

    if (std::strlen(string) + 1 == message.size())
    {
        return nullptr;
    }

    return message.data() + std::strlen(string) + 1;
}
