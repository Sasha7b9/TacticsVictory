// 2021/04/10 18:42:52 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by

#ifdef WIN32
#pragma warning(push, 0)
#pragma warning(disable:4702 4706)
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#include "../../ThirdParty/libevent/bufferevent_filter.c"
#include "../../ThirdParty/libevent/event.c"

#ifdef WIN32
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif
