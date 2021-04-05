// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once

#pragma warning(push, 0)

#include <Urho3D/AngelScript/APITemplates.h>
#include <Urho3D/Audio/Audio.h>
#include <Urho3D/Audio/Sound.h>
#include <Urho3D/Audio/SoundListener.h>
#include <Urho3D/Audio/SoundSource3D.h>
#include <Urho3D/Core/Profiler.h>
#include <Urho3D/Engine/Application.h>
#include <Urho3D/Engine/DebugHud.h>
#include <Urho3D/Engine/EngineDefs.h>
#include <Urho3D/Engine/Console.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/CustomGeometry.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Graphics/Geometry.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/IndexBuffer.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/ParticleEffect.h>
#include <Urho3D/Graphics/ParticleEmitter.h>
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/DropDownList.h>
#include <Urho3D/UI/FileSelector.h>
#include <Urho3D/UI/LineEdit.h>
#include <Urho3D/UI/ScrollBar.h>
#include <Urho3D/UI/Slider.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/Window.h>
#include <Urho3D/UI/CheckBox.h>
#include <Urho3D/UI/UIEvents.h>
#include <Urho3D/Urho2D/StaticSprite2D.h>
#include <Urho3D/Urho2D/Sprite2D.h>
#include <Urho3D/IO/IOEvents.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/IO/MemoryBuffer.h>
#ifdef SendMessage
#undef SendMessage
#endif
#include <Urho3D/Network/Network.h>
#include <Urho3D/Network/NetworkEvents.h>
#include <Urho3D/Network/Protocol.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Resource/ResourceEvents.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Resource/Localization.h>
#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/Core/CoreEvents.h>

using namespace Urho3D;

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include <cfloat>
#include <ctime>
#include <iostream>
#include <mutex>
#include <sstream>
#include <d3d9types.h>

#pragma warning(pop)

#include "defines.h"

#include "glob_engine.h"
#include "glob_game.h"

#include "Core/Structures_.h"
#include "FileSystem/ConfigurationFile_.h"
#include "Game/Logic/Rotator_.h"
#include "Game/Logic/SunEngine_.h"
#include "Graphics/Renderer_.h"
#include "Graphics/2D/Image_.h"
#include "GUI/Cursor_.h"
#include "GUI/Controls/Hint_.h"
#include "GUI/Controls/Label_.h"
#include "GUI/Logic/LineTranslator2D_.h"
#include "GUI/Menu/MenuEvents_.h"
#include "GUI/Windows/Console_.h"
#include "GUI/Windows/WindowVariables_.h"
#include "Input/Mouse_.h"
#include "Scene/Objects/Units/Air/AirPlane/AirPlane_.h"
#include "Scene/Objects/Units/Ground/Tank/Tank_.h"
#include "Scene/Terrain/Level_.h"
#include "Utils/GlobalFunctions_.h"
#include "Utils/Log_.h"
#include "Utils/SystemFunctions_.h"
#include "Utils/SystemUtils_.h"
