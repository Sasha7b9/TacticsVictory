// 2021/04/02 17:53:54 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once

#pragma warning(push, 0)

#define _WINSOCKAPI_
#include <windows.h>

#include <Urho3D/Engine/Application.h>
#include <Urho3D/Engine/EngineDefs.h>

#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/IO/Log.h>

using namespace Urho3D;

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include <sockpp/tcp_acceptor.h>
#include <sockpp/tcp_connector.h>

#include <iostream>
#include <map>
#include <mutex>

#pragma warning(pop)

#include "defines.h"
#include "glob_engine.h"
#include "glob_game.h"
#include "Utils/Log_.h"
