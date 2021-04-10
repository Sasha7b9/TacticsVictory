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

static void CallbackError(struct evconnlistener *, void *ptr);


static void SendString(void *bufevnt, pchar message);


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

    struct event *signal_event = evsignal_new(base, 2 /* SIGINT */, CallbackSignal, (void *)&base);

    if (!signal_event || event_add(signal_event, NULL) < 0)
    {
        LOGERROR("Could not create/add a signal event!");
        return;
    }

    evconnlistener_set_error_cb(listener, CallbackError);

    event_base_dispatch(base);

    evconnlistener_free(listener);
    event_free(signal_event);
    event_base_free(base);
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
    struct evbuffer *output = bufferevent_get_output(bev);

    if (evbuffer_get_length(output) == 0)
    {
        LOGWRITE("flushed answer");
        bufferevent_free(bev);
    }
}


static void CallbackRead(struct bufferevent *, void *)
{

}


static void CallbackError(struct evconnlistener *, void *)
{
    LOGERROR("Error occured");
}


static void CallbackEvents(struct bufferevent *bev, short events, void *)
{
    if (events & BEV_EVENT_READING)
    {
        LOGWRITE("Occured event reading");
    }
    else if (events & BEV_EVENT_WRITING)
    {
        LOGWRITE("Occured event writing");
    }
    else if (events & BEV_EVENT_EOF)
    {
        LOGWRITE("Occured event EOF");
    }
    else if (events & BEV_EVENT_ERROR)
    {
        char buffer[1024];
        LOGERRORF("Got an error on the connection: %s", strerror_s(buffer, 1024, errno));
    }
    else if (events & BEV_EVENT_TIMEOUT)
    {
        LOGWRITE("Occured event timeout");
    }
    else if (events & BEV_EVENT_CONNECTED)
    {
        LOGWRITE("Occured  event connected");
    }
    else
    {
        LOGERROR("An unknown event occured");
    }

    /* None of the other events can happen here, since we haven't enabled
     * timeouts */
//    bufferevent_free(bev);
}


void Server::AppendHandler(pchar command, pFuncVV handler)
{
    handlers[command] = handler;
}


void Server::AppendServerInfo(const ServerInfo &info)
{
    infos[info.address] = info;
}
