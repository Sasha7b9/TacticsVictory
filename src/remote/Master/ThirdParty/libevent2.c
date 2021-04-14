// 2021/04/10 18:42:52 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by

#ifdef WIN32
#pragma warning(push, 0)
#pragma warning(disable : 4706)
#endif

#ifdef WIN32
#include "../../ThirdParty/libevent/wepoll.c"
#else
#include "../../ThirdParty/libevent/poll.c"
#endif

#include "../../ThirdParty/libevent/bufferevent_pair.c"

#ifdef WIN32
#pragma warning(pop)
#endif
