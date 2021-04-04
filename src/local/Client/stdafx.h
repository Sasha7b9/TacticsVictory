// 2021/04/02 17:53:54 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once

#pragma warning(push, 0)

#define _WINSOCKAPI_
#include <windows.h>

#include <Urho3D/Audio/Audio.h>
#include <Urho3D/Audio/SoundListener.h>
#include <Urho3D/Engine/Application.h>
#include <Urho3D/Engine/EngineDefs.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/OctreeQuery.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/IO/MemoryBuffer.h>
#include <Urho3D/Math/Ray.h>
#include <Urho3D/Resource/Localization.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/CheckBox.h>
#include <Urho3D/UI/DropDownList.h>
#include <Urho3D/UI/LineEdit.h>
#include <Urho3D/UI/ScrollBar.h>
#include <Urho3D/UI/Slider.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/Window.h>
#include <Urho3D/Urho2D/Sprite2D.h>
#include <Urho3D/Urho2D/StaticSprite2D.h>

using namespace Urho3D;

#include <rapidjson/document.h>

#include <sockpp/tcp_acceptor.h>
#include <sockpp/tcp_connector.h>

#include <iostream>
#include <map>
#include <mutex>
#include <sstream>

#pragma warning(pop)

#include "defines.h"
#include "glob_engine.h"
#include "FileSystem/ConfigurationFile_.h"
#include "GUI/Cursor_.h"
#include "GUI/GUI.h"
#include "GUI/Controls/Hint_.h"
#include "GUI/Controls/Label_.h"
#include "GUI/Menu/Menu.h"
#include "GUI/Windows/Console_.h"
#include "GUI/Windows/WindowVariables_.h"
#include "Network/Other/MasterServer_.h"
#include "Utils/Log_.h"
#include "Utils/Settings_.h"
#include "Utils/StringUtils_.h"
#include "glob_game.h"
