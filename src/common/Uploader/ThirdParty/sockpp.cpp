// 2021/04/01 17:30:33 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"

#ifdef WIN32
#pragma warning(push, 0)
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#include "../../ThirdParty/sockpp/src/socket.cpp"
#include "../../ThirdParty/sockpp/src/acceptor.cpp"
#include "../../ThirdParty/sockpp/src/connector.cpp"
#include "../../ThirdParty/sockpp/src/stream_socket.cpp"
#include "../../ThirdParty/sockpp/src/exception.cpp"
#include "../../ThirdParty/sockpp/src/inet_address.cpp"

#ifdef WIN32
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif
