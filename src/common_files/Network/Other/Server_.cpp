// 2021/04/09 14:45:08 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "FileSystem/ConfigurationFile_.h"
#include "Network/Other/NetworkTypes_.h"
#include "Network/Other/Server_.h"


static const char MESSAGE[] = "Hello, World!";

// Вызывается при новом соединении
static void CallbackListener(struct evconnlistener *, evutil_socket_t, struct sockaddr *, int socklen, void *);
static void signal_cb(evutil_socket_t, short, void *);
static void conn_writecb(struct bufferevent *, void *);
static void conn_eventcb(struct bufferevent *, short, void *);


void Server::Run()
{
    struct sockaddr_in sin = { 0 };

#ifdef WIN32
    WSADATA wsa_data;
    WSAStartup(0x0201, &wsa_data);
#endif

    struct event_base *base = event_base_new();

    if (!base)
    {
        LOGERROR("Could not initialize libevent");
        return;
    }

    uint16 port = static_cast<uint16>(TheConfig.GetInt("port"));

    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);

    struct evconnlistener *listener = evconnlistener_new_bind(base, CallbackListener, (void *)base,
        LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, -1, (struct sockaddr *)&sin, sizeof(sin));

    if (listener)
    {
        LOGWRITEF("Bind to port %d is ok", port);
    }
    else
    {
        LOGERROR("Could not create a listener");
        return;
    }

    struct event *signal_event = evsignal_new(base, 2 /* SIGINT */, signal_cb, (void *)&base);

    if (!signal_event || event_add(signal_event, NULL) < 0)
    {
        LOGERROR("Could not create/add a signal event!");
        return;
    }

    event_base_dispatch(base);

    evconnlistener_free(listener);
    event_free(signal_event);
    event_base_free(base);
}


static void CallbackListener(struct evconnlistener *, evutil_socket_t fd, struct sockaddr *, int ,
    void *user_data)
{
    struct event_base *base = (event_base *)user_data;
    struct bufferevent *bev;

    bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);

    if (!bev)
    {
        fprintf(stderr, "Error constructing bufferevent!");
        event_base_loopbreak(base);
        return;
    }

    bufferevent_setcb(bev, NULL, conn_writecb, conn_eventcb, NULL);
    bufferevent_enable(bev, EV_WRITE);
    bufferevent_disable(bev, EV_READ);

    bufferevent_write(bev, MESSAGE, strlen(MESSAGE));
}


static void signal_cb(evutil_socket_t , short , void *user_data)
{
    struct event_base *base = (event_base *)user_data;
    struct timeval delay = { 2, 0 };

    LOGWRITE("Caught an interrupt signal; exiting cleanly in two seconds.");

    event_base_loopexit(base, &delay);
}


static void conn_writecb(struct bufferevent *bev, void *)
{
    struct evbuffer *output = bufferevent_get_output(bev);

    if (evbuffer_get_length(output) == 0)
    {
        LOGWRITE("flushed answer");
        bufferevent_free(bev);
    }
}


static void conn_eventcb(struct bufferevent *bev, short events, void *)
{
    if (events & BEV_EVENT_EOF)
    {
        LOGWRITE("Connection closed");
    }
    else if (events & BEV_EVENT_ERROR)
    {
        char buffer[1024];
        LOGERRORF("Got an error on the connection: %s", strerror_s(buffer, 1024, errno));
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
