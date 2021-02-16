// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once

#pragma warning(push, 0)

#include <Urho3D/AngelScript/Addons.h>
#include <Urho3D/AngelScript/APITemplates.h>
#include <Urho3D/AngelScript/Script.h>
#include <Urho3D/AngelScript/ScriptFile.h>
#include <Urho3D/AngelScript/ScriptInstance.h>

#include <Urho3D/Audio/Audio.h>
#include <Urho3D/Audio/Sound.h>
#include <Urho3D/Audio/SoundListener.h>
#include <Urho3D/Audio/SoundSource.h>
#include <Urho3D/Audio/SoundSource3D.h>

#include <Urho3D/Core/Mutex.h>
#include <Urho3D/Core/Profiler.h>
#include <Urho3D/Core/Thread.h>

#include <Urho3D/Engine/Application.h>
#include <Urho3D/Engine/DebugHud.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Engine/EngineDefs.h>
#include <Urho3D/Engine/Console.h>

#include <Urho3D/Graphics/BillboardSet.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/CustomGeometry.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Graphics/DecalSet.h>
#include <Urho3D/Graphics/Drawable.h>
#include <Urho3D/Graphics/Geometry.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/GraphicsDefs.h>
#include <Urho3D/Graphics/IndexBuffer.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/OctreeQuery.h>
#include <Urho3D/Graphics/ParticleEffect.h>
#include <Urho3D/Graphics/ParticleEmitter.h>
#include <Urho3D/Graphics/RenderSurface.h>
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/Graphics/Texture.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/VertexBuffer.h>
#include <Urho3D/Graphics/Zone.h>

#include <Urho3D/Input/Input.h>
#include <Urho3D/Input/InputEvents.h>

#include <Urho3D/Math/MathDefs.h>
#include <Urho3D/Math/Random.h>

#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/Cursor.h>
#include <Urho3D/UI/DropDownList.h>
#include <Urho3D/UI/FileSelector.h>
#include <Urho3D/UI/LineEdit.h>
#include <Urho3D/UI/ScrollBar.h>
#include <Urho3D/UI/Sprite.h>
#include <Urho3D/UI/Slider.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/Window.h>
#include <Urho3D/UI/CheckBox.h>
#include <Urho3D/UI/UIEvents.h>

#include <Urho3D/Urho2D/StaticSprite2D.h>
#include <Urho3D/Urho2D/Sprite2D.h>

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

#include <Urho3D/Core/Timer.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Core/ProcessUtils.h>

#include <Urho3D/DebugNew.h>

#include <Urho3d/ThirdParty/AngelScript/angelscript.h>

using namespace Urho3D;

#include <cfloat>
#include <ctime>
#include <sstream>
#include <d3d9types.h>

#pragma warning(pop)

#include "defines.h"
#include "GlobalFunctions.h"
#include "LogRTS.h"
#include "SettingsTypes.h"
#include "Battler.h"

#include "Audio/Sounds.h"

#include "Core/_Math.h"

#include "Editor/Editor.h"

#include "Game/Particles.h"
#include "Game/Logic/Movinator.h"
#include "Game/Logic/Rotator.h"
#include "Game/Path/TilePath.h"

#include "Graphics/2D/Image.h"
#include "Graphics/Objects/Triangle.h"

#include "GUI/Cursor.h"
#include "GUI/GUI.h"
#include "GUI/Controls/_Button.h"
#include "GUI/Controls/_ButtonSwitch.h"
#include "GUI/Controls/_ButtonToggled.h"
#include "GUI/Controls/_DropDownListWithTextAndButton.h"
#include "GUI/Controls/_GovernorFloat.h"
#include "GUI/Controls/_Hint.h"
#include "GUI/Controls/_Label.h"
#include "GUI/Controls/_Slider.h"
#include "GUI/Controls/_SliderInt.h"
#include "GUI/Controls/_SliderWithTextAndButtons.h"
#include "GUI/Controls/_Tab.h"
#include "GUI/Logic/LineTranslator2D.h"
#include "GUI/GuiEditor/GuiEditor.h"
#include "GUI/GuiGame/ContextMenuUnit.h"
#include "GUI/GuiGame/GuiGame.h"
#include "GUI/GuiGame/WindowTarget.h"
#include "GUI/Menu/MenuAboutMe.h"
#include "GUI/Menu/MenuConfirmExit.h"
#include "GUI/Menu/MenuEvents.h"
#include "GUI/Menu/MenuGame.h"
#include "GUI/Menu/MenuOptions.h"
#include "GUI/Menu/MenuRTS.h"
#include "GUI/Panels/PanelBottom.h"
#include "GUI/Panels/PanelMain.h"
#include "GUI/Panels/PanelMap.h"
#include "GUI/Windows/Console.h"
#include "GUI/Windows/WindowVariables.h"

#include "Scene/_Level.h"
#include "Scene/_Scene.h"
#include "Scene/Cameras/Camera.h"
#include "Scene/Objects/Ammo/_AmmoObject.h"
#include "Scene/Objects/Ammo/Rocket/Rocket.h"
#include "Scene/Objects/Buildings/MilitaryPlant/MilitaryPlant.h"
#include "Scene/Objects/Terrain/SegmentTerrain.h"
#include "Scene/Objects/Units/Tank/_Tank.h"

#include "glob_engine.h"
#include "glob_game.h"
#include "Settings.h"
