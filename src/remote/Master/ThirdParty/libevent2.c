// 2021/04/10 18:42:52 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by

#ifdef WIN32
#pragma warning(push, 0)
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#ifdef WIN32
#include "../../ThirdParty/libevent/wepoll.c"
#include "../../ThirdParty/libevent/win32select.c"
#else
#include "../../ThirdParty/libevent/poll.c"
#include "../../ThirdParty/libevent/select.c"
#endif

#include "../../ThirdParty/libevent/bufferevent_pair.c"

#ifdef WIN32
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif
