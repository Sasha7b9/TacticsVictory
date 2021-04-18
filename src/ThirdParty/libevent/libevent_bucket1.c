// 2021/04/10 18:42:52 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by

#ifdef WIN32
#pragma warning(push, 0)
#pragma warning(disable:4702 4706)
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
#endif

#ifdef WIN32
#include "bufferevent_async.c"
#include "buffer_iocp.c"
#include "event_iocp.c"
#endif

#include "buffer.c"
#include "bufferevent.c"
#include "bufferevent_ratelim.c"
#include "bufferevent_sock.c"
#include "epoll.c"
#include "evmap.c"
#include "evthread.c"
#include "evutil.c"
#include "evutil_rand.c"
#include "evutil_time.c"
#include "listener.c"
#include "log.c"
#include "signal.c"
#include "strlcpy.c"

#ifdef WIN32
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif
