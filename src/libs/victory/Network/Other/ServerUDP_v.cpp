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

    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(port);

#ifdef WIN32

    if (bind((SOCKET)sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
#else
    if (bind((int)sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
#endif
    {
        LOGERROR("Can not bind to port");
    }
    else
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


void ServerUDP::SendAnswer(void *bev, uint id, pchar message, void *data, uint size_data)
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


void ServerUDP::SendAnswer(void *bev, uint id, pchar message, pchar data)
{
    SendAnswer(bev, id, message, (void *)data, (uint)std::strlen(data) + 1);
}


void ServerUDP::SendAnswer(void *bev, uint id, pchar message, int value)
{
    SendAnswer(bev, id, message, &value, sizeof(value));
}


void ServerUDP::CallbackRead(evutil_socket_t sock, short /*event*/, void *)
{
    char buf[1024] = "";

    socklen_t size = sizeof(struct sockaddr);

    struct sockaddr_in client_addr = { 0 };

#ifdef WIN32
    int len = recvfrom((SOCKET)sock, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr, &size);
#else
    int len = recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr, &size);
#endif

    if (len < 0)
    {
        LOGERROR("Server recv message error");
        return;
    }
    else if (len == 0)
    {
        LOGERROR("Connetioin closed");
    }
    else
    {
        LOGWRITEF("From %s:%d : \"%s\"", inet_ntoa(client_addr.sin_addr), client_addr.sin_port, buf);
    }

#ifdef WIN32
    sendto((SOCKET)sock, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr, size);
#else
    sendto(sock, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr, size);
#endif
}


void ServerUDP::ProcessClient(ClientInfo &info, ServerUDP *server)
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


void ServerUDP::CallbackError(struct bufferevent *bev, short error, void *_args)
{
    ServerUDP *server = ((CallbackArgs *)_args)->server;

    if (error & BEV_EVENT_READING)
    {
        LOGWRITEF("Client %s disconnected", server->clients[bev].address.ToStringFull().c_str());

        server->clients.erase(bev);
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


void ServerUDP::AppendHandler(pchar command, handlerClient handler)
{
    handlers[command] = handler;
}
