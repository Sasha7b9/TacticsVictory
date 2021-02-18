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

#include "glob_engine.h"
#include "glob_game.h"

#include "Game/Logic/_TRotator.h"
#include "Game/Path/TPathIndicator.h"
#include "Game/Path/TTilePath.h"

#include "Graphics/2D/TImage.h"

#include "GUI/TCursor.h"
#include "GUI/TGUI.h"
#include "GUI/Controls/_TButton.h"
#include "GUI/Controls/_TButtonSwitch.h"
#include "GUI/Controls/_TButtonToggled.h"
#include "GUI/Controls/_TDropDownListWithTextAndButton.h"
#include "GUI/Controls/_TGovernorFloat.h"
#include "GUI/Controls/_THint.h"
#include "GUI/Controls/_TLabel.h"
#include "GUI/Controls/_TSlider.h"
#include "GUI/Controls/_TSliderInt.h"
#include "GUI/Controls/_TSliderWithTextAndButtons.h"
#include "GUI/Controls/_TTab.h"
#include "GUI/Logic/TLineTranslator2D.h"
#include "GUI/GuiEditor/TGuiEditor.h"
#include "GUI/GuiGame/TContextMenuUnit.h"
#include "GUI/GuiGame/TGuiGame.h"
#include "GUI/GuiGame/TWindowTarget.h"
#include "GUI/Menu/TMenuAboutMe.h"
#include "GUI/Menu/TMenuConfirmExit.h"
#include "GUI/Menu/TMenuEvents.h"
#include "GUI/Menu/TMenuGame.h"
#include "GUI/Menu/TMenuOptions.h"
#include "GUI/Menu/TMenu.h"
#include "GUI/Menu/TMenuStart.h"
#include "GUI/Panels/TPanelBottom.h"
#include "GUI/Panels/TPanelMain.h"
#include "GUI/Panels/TPanelMap.h"
#include "GUI/Windows/TConsole.h"
#include "GUI/Windows/TWindowVariables.h"

#include "Scene/_TLevel.h"
#include "Scene/TCScene.h"
#include "Scene/Cameras/TCamera.h"
#include "Scene/Objects/_TGameObjectEvents.h"
#include "Scene/Objects/_TObjectState.h"
#include "Scene/Objects/Ammo/_TAmmoObject.h"
#include "Scene/Objects/Ammo/Rocket/TCRocket.h"
#include "Scene/Objects/Buildings/_TBuildingObject.h"
#include "Scene/Objects/Terrain/_TCornerCube.h"
#include "Scene/Objects/Terrain/_TEdgeCube.h"
#include "Scene/Objects/Terrain/_TLayerTerrain.h"
#include "Scene/Objects/Terrain/_TSegmentTerrain.h"
#include "Scene/Objects/Terrain/_TSideCube.h"
#include "Scene/Objects/Units/Logic/_TTranslator.h"
#include "Scene/Objects/Units/_TUnitObject.h"
#include "Scene/Objects/Weapons/_TWeaponObject.h"
#include "Scene/Primitives/_TTriangle.h"

#include "Utils/TGlobalFunctions.h"
#include "Utils/TCLog.h"
#include "Utils/TSettings.h"
#include "Utils/TSettingsTypes.h"
