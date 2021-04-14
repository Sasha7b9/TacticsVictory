// 2021/04/02 17:15:01 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once

#ifdef WIN32
#pragma warning(push, 0)
#endif

#ifndef WIN32
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wclass-memaccess"
#endif
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#ifndef WIN32
#pragma GCC diagnostic pop
#endif

#ifdef WIN32
#define _WINSOCKAPI_
#include <windows.h>
#endif

#include <Urho3D/Math/Vector2.h>

using namespace Urho3D;

#include <cstdarg>
#include <iostream>
#include <locale>
#include <map>
#include <mutex>
#include <vector>

#include <sockpp/tcp_acceptor.h>
#include <sockpp/tcp_connector.h>

#ifdef WIN32
#pragma warning(pop)
#endif

#include "defines.h"
#include "globals.h"
#include "Utils/Log_.h"
