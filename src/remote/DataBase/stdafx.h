// 2021/04/02 17:15:01 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once

#pragma warning(push, 0)

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>

#define _WINSOCKAPI_
#include <windows.h>

#include <Urho3D/Math/Vector2.h>

using namespace Urho3D;

#include <cstdarg>
#include <locale>
#include <map>
#include <mutex>
#include <vector>

#include <sockpp/tcp_acceptor.h>
#include <sockpp/tcp_connector.h>

#pragma warning(pop)

#include "defines.h"

#include "FileSystem/ConfigurationFile_.h"
#include "Network/Other/MasterServer_.h"
#include "Utils/Log_.h"

#include "globals.h"
