// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include <stdafx.h>
#include "Battle.h"
#include "GUI/GUI.h"
#include "GUI/Widgets/DrawingWidget.h"
#include "GUI/Widgets/CursorGUI.h"
#include "GUI/Widgets/Console.h"
#include "Scene/Cameras/CameraRTS.h"
#include "Objects/Units/Ground/Tank.h"
#include "Scene/World/GameWorld.h"
#include "Input/Input.h"
#include "Input/Mouse.h"
#include "GUI/Mutators/MovementMutator.h"
#include "Sounds/SoundPlayer.h"
#include "Utils/Log.h"
#include "Scene/World/Landscape.h"
#include "GUI/Widgets/ObjectViewportWidget.h"
#include "Objects/Units/Logic/PathFinder/PathFinder.h"
#include "Graphics/Textures/PoolTextures.h"
#include "Graphics/Geometry/PoolGeometry.h"


using namespace std;
using namespace std::filesystem;
using namespace Pi;

static String<> commandLine;

PI_ENTER_POINT(Battle)


Battle *Battle::self = nullptr;


Battle::Battle()
    : Singleton<Battle>(self)
{
    uint64 timeEnter = TheTimeMgr->GetMicrosecondCount();

    PoolTextures::Construct();
    PoolGeometry::Construct();

    new CameraRTS();

    TheWorldMgr->SetWorldCreator(&ConstructWorld);

    Input::Init();

    TheDisplayMgr->InstallDisplayEventHandler(&displayEventHandler);

    TheInterfaceMgr->SetInputManagementMode(InputManagementMode::Automatic);
    TheMessageMgr->BeginSinglePlayerGame();

    new Mouse();

    GUI::Create();

    GameObject::Construct();

    CreateScene();

    float halfDisplayWidth = 0.5f * static_cast<float>(TheDisplayMgr->GetDisplayWidth());
    float halfDisplayHeight = 0.5f * static_cast<float>(TheDisplayMgr->GetDisplayHeight());

    CursorGUI::self->position = Vector2D(halfDisplayWidth, halfDisplayHeight);
    CursorGUI::self->Invalidate();

    new SoundPlayer();

    float timeConstructor = (float) (TheTimeMgr->GetMicrosecondCount() - timeEnter) * 1e-6f;

    CreateCommands();

    LOG_WRITE("Game constructor %f seconds", timeConstructor);
}

Battle::~Battle()
{
    SAFE_DELETE(CameraRTS::self);
    SAFE_DELETE(Mouse::self);
    SAFE_DELETE(GUI::self);
    TheWorldMgr->UnloadWorld();
    TheWorldMgr->SetWorldCreator(nullptr);
    TheMessageMgr->EndGame();
    SAFE_DELETE(SoundPlayer::self);
    GameObject::Destruct();
    PoolGeometry::Destruct();
    PoolTextures::Destruct();
}

void Battle::CreateScene()
{
    TheWorldMgr->LoadWorld("world/Empty");
}


void Battle::CreateCommands()
{
    TheEngine->AddCommand(new Command("gizmo", &gizmoCommandObserver, {"enable/disable units gizmo"}));

    TheEngine->AddCommand(new Command("waterFogDensity", &fogDensityCommandObserver, {"set fog density for water"}));
}


World *Battle::ConstructWorld(pchar name, void *)
{
    new GameWorld(name);

    return GameWorld::self;
}


string Battle::DataPath() const
{
    return current_path().string() + "/Data/TacticsVictory/";
}


void Battle::ReloadLandscape() const
{
    LOG_WRITE("Need reload landscape");
}
