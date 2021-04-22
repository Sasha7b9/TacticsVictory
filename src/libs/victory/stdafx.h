// 2021/04/22 11:56:38 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once

#pragma warning(push, 0)

#define _WINSOCKAPI_
#include <windows.h>

#include <Urho3D/Container/Str.h>
#include <Urho3D/Core/StringUtils.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/UI/FileSelector.h>
#include <Urho3D/UI/Window.h>


#undef Bool
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>


#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>


#pragma warning(pop)


using namespace Urho3D;


#include "defines.h"
#include "victory.h"
