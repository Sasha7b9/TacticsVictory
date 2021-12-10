// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include <stdafx.h>
#include "Battle.h"
#include "GUI/GUI.h"
#include "GUI/Widgets/DrawingWidget.h"
#include "GUI/Widgets/CursorGUI.h"
#include "GUI/Widgets/Console.h"
#include "Scene/Cameras/CameraRTS.h"
#include "Scene/Objects/Units/Ground/Tank.h"
#include "Scene/World/GameWorld.h"
#include "Input/Input.h"
#include "Input/Mouse.h"
#include "GUI/Mutators/MovementMutator.h"
#include "Sounds/SoundPlayer.h"
#include "Utils/Log.h"
#include "Scene/World/Landscape.h"
#include "GUI/Widgets/ObjectViewportWidget.h"
#include "Scene/Objects/Units/PathFinder/PathUnit.h"


using namespace Pi;

static String<> commandLine;

PI_ENTER_POINT(Battle)


using namespace std;
using namespace std::filesystem;


namespace Pi
{
    Battle *Battle::self = nullptr;
}


Battle::Battle()
    : Singleton<Battle>(self),
    displayEventHandler(&HandleDisplayEvent),
    locatorReg(kLocatorSpectator, "Spectator Camera")
{
    uint64 timeEnter = TheTimeMgr->GetMicrosecondCount();

    new CameraRTS();

    TheWorldMgr->SetWorldCreator(&ConstructWorld);

    Input::Init();

    TheDisplayMgr->InstallDisplayEventHandler(&displayEventHandler);

    TheInterfaceMgr->SetInputManagementMode(InputManagementMode::Automatic);
    TheMessageMgr->BeginSinglePlayerGame();

    new Mouse();

    GUI::Create();

    CreateScene();

    new PathUnit();

    float halfDisplayWidth = 0.5f * static_cast<float>(TheDisplayMgr->GetDisplayWidth());
    float halfDisplayHeight = 0.5f * static_cast<float>(TheDisplayMgr->GetDisplayHeight());

    CursorGUI::self->position = Vector2D(halfDisplayWidth, halfDisplayHeight);
    CursorGUI::self->Invalidate();

    new SoundPlayer();

//    TheGraphicsMgr->SetDiagnosticFlags(TheGraphicsMgr->GetDiagnosticFlags() | PiFlagDiagnostic::Normals);

    float timeConstructor = (float) (TheTimeMgr->GetMicrosecondCount() - timeEnter) * 1e-6f;

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
}

void Battle::CreateScene()
{
    TheWorldMgr->LoadWorld("world/Empty");
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
