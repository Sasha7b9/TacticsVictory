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

    TheInterfaceMgr->SetInputManagementMode(InputManagementMode::Automatic);

    new Mouse();

    GUI::Create();

    GameObject::Construct();

    TheWorldMgr->LoadWorld("world/Empty");

    CursorGUI::self->position = Vector2D((float)TheDisplayMgr->GetDisplayWidth() / 2.0f,
                                         (float)TheDisplayMgr->GetDisplayHeight() / 2.0f);
    CursorGUI::self->Invalidate();

    new SoundPlayer();

    float timeConstructor = (float) (TheTimeMgr->GetMicrosecondCount() - timeEnter) * 1e-6f;

    CreateCommands();

    TheMessageMgr->EndGame();

    TheNetworkMgr->NetworkTask();

    TheNetworkMgr->SetProtocol(kGameProtocol);
    TheNetworkMgr->SetPortNumber(0);
    TheNetworkMgr->SetBroadcastPortNumber(PORT_NUMBER);
    PiResultNetwork::B result = TheMessageMgr->BeginMultiplayerGame(false);

    if (result != PiResultNetwork::Okay)
    {
        LOG_ERROR_TRACE("Can not begin mulitplayer game");
    }

    NetworkAddress address = MessageMgr::StringToAddress(REMOTE_ADDRESS);
    address.SetPort(PORT_NUMBER);

    result = TheMessageMgr->Connect(address);

    if (result != PiResultNetwork::Okay)
    {
        LOG_ERROR_TRACE("Can not connect to %s:%d", REMOTE_ADDRESS, PORT_NUMBER);
    }
    else
    {
        LOG_WRITE("Attempt connection to %s:%d ...", REMOTE_ADDRESS, PORT_NUMBER);
    }

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


void Battler::CreateCommands()
{
    TheEngine->AddCommand(new Command("gizmo", &gizmoCommandObserver, {"enable/disable units gizmo"}));

    TheEngine->AddCommand(new Command("waterFogDensity", &fogDensityCommandObserver, {"set fog density for water"}));

    TheEngine->AddCommand(new Command("ping", &pingCommandObserver, {"reques for ping. type \"ping period times\""}));
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
