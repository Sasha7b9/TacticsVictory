// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once

#ifdef WIN32
#pragma warning(push, 0)
#endif

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#define _WINSOCKAPI_
#include <windows.h>


#include <Urho3D/AngelScript/Addons.h>
#include <Urho3D/AngelScript/APITemplates.h>
#include <Urho3D/AngelScript/Script.h>
#include <Urho3D/AngelScript/ScriptFile.h>
#include <Urho3D/AngelScript/ScriptInstance.h>
#include <Urho3D/Container/HashMap.h>
#include <Urho3D/Core/Mutex.h>
#include <Urho3D/Core/Profiler.h>
#include <Urho3D/Core/Thread.h>
#include <Urho3D/Core/Timer.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Core/ProcessUtils.h>
#include <Urho3D/Engine/Application.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Engine/EngineDefs.h>
#include <Urho3D/Graphics/Geometry.h>
#include <Urho3D/Graphics/IndexBuffer.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/VertexBuffer.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/Math/MathDefs.h>
#include <Urho3D/Math/Random.h>
#include <Urho3D/IO/IOEvents.h>
#include <Urho3D/IO/File.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/IO/MemoryBuffer.h>
#include <Urho3D/Math/Sphere.h>

#ifdef SendMessage
#undef SendMessage
#endif

#include <Urho3D/Network/Network.h>
#include <Urho3D/Network/NetworkEvents.h>
#include <Urho3D/Network/Protocol.h>
#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Physics/PhysicsEvents.h>
#include <Urho3D/Resource/ResourceEvents.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Resource/XMLFile.h>
#include <Urho3D/Resource/Localization.h>
#include <Urho3D/Resource/JSONFile.h>
#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/UI/Window.h>
#include <Urho3D/DebugNew.h>

using namespace Urho3D;

#include <sockpp/tcp_acceptor.h>
#include <sockpp/tcp_connector.h>

#include <cfloat>
#include <ctime>
#include <iostream>
#include <map>
#include <mutex>
#include <sstream>

#ifdef WIN32
#pragma warning(pop)
#endif

#include "defines.h"

#include "glob_engine.h"
#include "glob_game.h"

#include "Core/Structures_.h"
#include "FileSystem/ConfigurationFile_.h"
#include "Network/Other/Server_.h"
#include "Utils/Log_.h"
#include "Utils/StringUtils_.h"
