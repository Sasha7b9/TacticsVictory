// 2021/04/10 18:42:52 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by

#ifdef WIN32
#pragma warning(push, 0)
#pragma warning(disable : 4702 4706)
#endif

#ifdef WIN32
#include "../../ThirdParty/libevent/bufferevent_async.c"
#include "../../ThirdParty/libevent/buffer_iocp.c"
#include "../../ThirdParty/libevent/event_iocp.c"
#endif

#include "../../ThirdParty/libevent/buffer.c"
#include "../../ThirdParty/libevent/bufferevent.c"
#include "../../ThirdParty/libevent/bufferevent_ratelim.c"
#include "../../ThirdParty/libevent/bufferevent_sock.c"
#include "../../ThirdParty/libevent/epoll.c"
#include "../../ThirdParty/libevent/evmap.c"
#include "../../ThirdParty/libevent/evthread.c"
#include "../../ThirdParty/libevent/evutil.c"
#include "../../ThirdParty/libevent/evutil_rand.c"
#include "../../ThirdParty/libevent/evutil_time.c"
#include "../../ThirdParty/libevent/listener.c"
#include "../../ThirdParty/libevent/log.c"
#include "../../ThirdParty/libevent/signal.c"
#include "../../ThirdParty/libevent/strlcpy.c"

#ifdef WIN32
#pragma warning(pop)
#endif
