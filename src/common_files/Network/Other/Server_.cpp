// 2021/04/09 14:45:08 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "FileSystem/ConfigurationFile_.h"
#include "Network/Other/NetworkTypes_.h"
#include "Network/Other/Server_.h"


static const char MESSAGE[] = "Hello, World!";

// Вызывается при новом соединении
static void CallbackListener(struct evconnlistener *, evutil_socket_t, struct sockaddr *, int socklen, void *);
static void CallbackSignal(evutil_socket_t, short, void *);
static void CallbackEvents(struct bufferevent *, short, void *);
static void CallbackRead(struct bufferevent *, void *);
static void CallbackWrite(struct bufferevent *, void *);
static void CallbackAccept(evutil_socket_t listener, short event, void *arg);
static void CallbackError(struct bufferevent *bev, short what, void *ctx);


static void SendString(void *bufevnt, pchar message);

static void CallbackLog(int, const char *);


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


static void CallbackAccept(evutil_socket_t listener, short event, void *arg)
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
        bufferevent_setwatermark(bev, EV_READ, 0, 16384);
        bufferevent_enable(bev, EV_READ | EV_WRITE);
    }
}


static void CallbackListener(struct evconnlistener *, evutil_socket_t fd, struct sockaddr *addr, int ,
    void *user_data)
{
    sockaddr_in &sin = (sockaddr_in &)*addr;
    
    LOGWRITEF("Connection from %d.%d.%d.%d:%d accepted",
        sin.sin_addr.S_un.S_un_b.s_b1,
        sin.sin_addr.S_un.S_un_b.s_b2,
        sin.sin_addr.S_un.S_un_b.s_b3,
        sin.sin_addr.S_un.S_un_b.s_b4,
        sin.sin_port);

    struct event_base *base = (event_base *)user_data;

    struct bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);

    if (!bev)
    {
        fprintf(stderr, "Error constructing bufferevent!");
        event_base_loopbreak(base);
        return;
    }

    bufferevent_setcb(bev, CallbackRead, CallbackWrite, CallbackEvents, NULL);
    bufferevent_enable(bev, EV_TIMEOUT);
    bufferevent_enable(bev, EV_WRITE);
    bufferevent_enable(bev, EV_READ);
    bufferevent_enable(bev, EV_SIGNAL);
    bufferevent_enable(bev, EV_CLOSED);


//    SendString(bev, MESSAGE);
}


static void SendString(void *bufevnt, pchar message)
{
    uint size = (uint)std::strlen(message);

    bufferevent_write((bufferevent *)bufevnt, &size, 4);

    bufferevent_write((bufferevent *)bufevnt, message, size);
}


static void CallbackSignal(evutil_socket_t , short , void *user_data)
{
    struct event_base *base = (event_base *)user_data;
    struct timeval delay = { 2, 0 };

    LOGWRITE("Caught an interrupt signal; exiting cleanly in two seconds.");

    event_base_loopexit(base, &delay);
}


static void CallbackWrite(struct bufferevent *bev, void *)
{
    LOGWRITE(__FUNCTION__);

    struct evbuffer *output = bufferevent_get_output(bev);

    if (evbuffer_get_length(output) == 0)
    {
        LOGWRITE("flushed answer");
        bufferevent_free(bev);
    }
}


static void CallbackRead(struct bufferevent *bev, void *)
{
    struct evbuffer *input = bufferevent_get_input(bev);

    size_t n = 0;

    char *buf = evbuffer_readln(input, &n, EVBUFFER_EOL_ANY);

    LOGWRITE(__FUNCTION__);
}


static void CallbackError(struct bufferevent *bev, short what, void *ctx)
{
    LOGERROR("Error occured");
}


static void CallbackEvents(struct bufferevent *bev, short events, void *)
{
    LOGWRITE(__FUNCTION__);

    if (events & BEV_EVENT_READING)
    {
        LOGWRITE("Occured event reading");
    }
    
    if (events & BEV_EVENT_WRITING)
    {
        LOGWRITE("Occured event writing");
    }
    
    if (events & BEV_EVENT_EOF)
    {
        LOGWRITE("Occured event EOF");
    }
    
    if (events & BEV_EVENT_ERROR)
    {
        char buffer[1024];
        LOGERRORF("Got an error on the connection: %s", strerror_s(buffer, 1024, errno));
    }
    
    if (events & BEV_EVENT_TIMEOUT)
    {
        LOGWRITE("Occured event timeout");
    }
    
    if (events & BEV_EVENT_CONNECTED)
    {
        LOGWRITE("Occured  event connected");
    }

    /* None of the other events can happen here, since we haven't enabled
     * timeouts */
    bufferevent_free(bev);
}


void Server::AppendHandler(pchar command, pFuncVV handler)
{
    handlers[command] = handler;
}


void Server::AppendServerInfo(const ServerInfo &info)
{
    infos[info.address] = info;
}
