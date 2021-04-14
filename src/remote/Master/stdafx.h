// Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


#ifdef WIN32
#pragma warning(push, 0)
#endif

#include <cstdarg>
#include <iostream>
#include <istream>
#include <map>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#undef Bool
#ifndef WIN32
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wclass-memaccess"
#endif
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#ifndef WIN32
#pragma GCC diagnostic pop
#endif

#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>

#ifdef WIN32
    #pragma warning(pop)
#endif

#include "defines.h"
#include "globals.h"
#include "Utils/Log_.h"
