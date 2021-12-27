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
    uint64 timeEnter = TheTimeMgr->GetMicrosecondCount();

    PoolTextures::Construct();
    PoolGeometry::Construct();

    CameraRTS::Create();

    TheWorldMgr->SetWorldCreator(&ConstructWorld);

    Input::Init();

    TheInterfaceMgr->SetInputManagementMode(InputManagementMode::Automatic);

    Mouse::Create();

    GUI::Create();

    GameObject::Construct();

    TheWorldMgr->LoadWorld("world/Empty");

    CursorGUI::self->position = Vector2D((float)TheDisplayMgr->GetDisplayWidth() / 2.0f,
                                         (float)TheDisplayMgr->GetDisplayHeight() / 2.0f);
    CursorGUI::self->Invalidate();

    SoundPlayer::Create();

    float timeConstructor = (float) (TheTimeMgr->GetMicrosecondCount() - timeEnter) * 1e-6f;

    CreateCommands();

    ListPeriodicTask::Self()->Append(TaskConnecting::Self(), 1000);
    ListPeriodicTask::Self()->Append(TaskProfilerLastFrame::Self(), 1000);
    ListPeriodicTask::Self()->Append(TaskPing::Self(), 1000);

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
    ListPeriodicTask::Self()->Purge();
    Log::Destruct();
}


void Battler::ApplicationTask()
{
    uint time = TheTimeMgr->GetMillisecondCount();
    static uint timeNext = time;

    if(time >= timeNext)
    {
        timeNext += 100;

        ListPeriodicTask::Self()->Run();
    }
}


void Battler::CreateCommands()
{
    TheEngine->AddCommand(new Command("gizmo",           &gizmoCommandObserver, {"enable/disable units gizmo"}));
    TheEngine->AddCommand(new Command("waterFogDensity", &fogDensityCommandObserver, {"set fog density for water"}));
    TheEngine->AddCommand(new Command("ping",            &pingCommandObserver, {"reques for ping. type \"ping period times\""}));
    TheEngine->AddCommand(new Command("traffic",         &trafficCommandObserver, {"indicate info for recv/send traffic"}));
    TheEngine->AddCommand(new Command("s",               &serverCommandObserver, {"send command to server"}));
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
