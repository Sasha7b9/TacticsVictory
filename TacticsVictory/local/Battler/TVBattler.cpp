// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "TVBattler.h"
#include "GUI/GUI.h"
#include "GUI/Widgets/DrawingWidget.h"
#include "GUI/Widgets/CursorGUI.h"
#include "GUI/Widgets/Console.h"
#include "Scene/Cameras/CameraRTS.h"
#include "Objects/Units/Ground/Tank_.h"
#include "Scene/World/GameWorld.h"
#include "Input/Input.h"
#include "Input/Mouse.h"
#include "GUI/Mutators/MovementMutator.h"
#include "Sounds/SoundPlayer.h"
#include "Scene/World/Landscape_.h"
#include "GUI/Widgets/ObjectViewportWidget.h"
#include "Objects/Units/Logic/PathFinder/PathFinder.h"
#include "Graphics/Textures/PoolTextures.h"
#include "Graphics/Geometry/PoolGeometry.h"


using namespace std;
using namespace std::filesystem;
using namespace Pi;

static String<> commandLine;

PI_ENTER_POINT(Battler)


Battler *Battler::self = nullptr;


Battler::Battler() : Singleton<Battler>(self)
{
    Log::Construct(FlagLog::All, DirectionLog::EngineReport | DirectionLog::File);

    uint64 timeEnter = TheTimeMgr->GetMicrosecondCount();

    PoolTextures::Construct();
    PoolGeometry::Construct();

    new CameraRTS();

    TheWorldMgr->SetWorldCreator(&ConstructWorld);

    Input::Init();

    TheDisplayMgr->InstallDisplayEventHandler(&displayEventHandler);

    TheInterfaceMgr->SetInputManagementMode(InputManagementMode::Automatic);

    new Mouse();

    GUI::Create();

    GameObject::Construct();

    CreateScene();

    CursorGUI::self->position = Vector2D((float)TheDisplayMgr->GetDisplayWidth() / 2.0f,
                                         (float)TheDisplayMgr->GetDisplayHeight() / 2.0f);
    CursorGUI::self->Invalidate();

    new SoundPlayer();

    float timeConstructor = (float) (TheTimeMgr->GetMicrosecondCount() - timeEnter) * 1e-6f;

    CreateCommands();

    LOG_WRITE("Game constructor %f seconds", timeConstructor);
}

Battler::~Battler()
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
    Log::Destruct();
}

void Battler::CreateScene()
{
    TheWorldMgr->LoadWorld("world/Empty");
}


void Battler::CreateCommands()
{
    TheEngine->AddCommand(new Command("gizmo", &gizmoCommandObserver, {"enable/disable units gizmo"}));

    TheEngine->AddCommand(new Command("waterFogDensity", &fogDensityCommandObserver, {"set fog density for water"}));
}


World *Battler::ConstructWorld(pchar name, void *)
{
    new GameWorld(name);

    return GameWorld::self;
}


string Battler::DataPath() const
{
    return current_path().string() + "/Data/TacticsVictory/";
}


void Battler::ReloadLandscape() const
{
    Landscape::self->Reload();
}
