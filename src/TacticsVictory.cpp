#include <stdafx.h>


#include "GUI/GUI.h"
#include "Core/Camera.h"
#include "Editor/Editor.h"
#include "Game/Scene.h"
#include "Game/Path/TilePath.h"
#include "Game/Logic/Rotator.h"
#include "Game/Logic/Movinator.h"
#include "GUI/GuiGame/GuiGame.h"
#include "GUI/GuiEditor/GuiEditor.h"
#include "GUI/Elements/Image.h"
#include "TacticsVictory.h"
#include "Game/Level.h"
#include "GlobalFunctions.h"
#include "Game/Objects/Ammo/Rocket/Rocket.h"
#include "Game/Objects/Terrain/SegmentTerrain.h"


#pragma warning(push)
#pragma warning(disable:4100)
URHO3D_DEFINE_APPLICATION_MAIN(TacticsVictory)
#pragma warning(pop)



TacticsVictory::TacticsVictory(Context* context) :
    Application(context)
{
    gContext = context;
}

void TacticsVictory::Setup()
{
    gSet = new Settings();
    gFileSystem = GetSubsystem<FileSystem>();
    gSet->Load();

    engineParameters_["WindowTitle"] = GetTypeName();
    engineParameters_["LogName"] = GetSubsystem<FileSystem>()->GetAppPreferencesDir("urho3d", "logs") + GetTypeName() + ".log";
    engineParameters_["FullScreen"] = false;
    engineParameters_["Headless"] = false;
    engineParameters_["TextureQuality"] = 32;
    engineParameters_["WindowWidth"] = gSet->GetInt(TV_SCREEN_WIDTH);
    engineParameters_["WindowHeight"] = gSet->GetInt(TV_SCREEN_HEIGHT);
}

void TacticsVictory::Stop()
{
    TilePath::RemoveAll();
    Rocket::DeleteAll();
    SAFE_DELETE(scene);
    SAFE_DELETE(gFileSelector);
    SAFE_DELETE(gTerrain);
    SAFE_DELETE(gLevel);
    SAFE_DELETE(gGUI);
    File file(gContext, "ui.xml", Urho3D::FILE_WRITE);
    URHO3D_LOGINFO("Now save ui");
    gUIRoot->SaveXML(file);
    gSet->Save();
    SAFE_DELETE(gSet);
    engine_->DumpResources(true);
    SAFE_DELETE(gEditor);
    SAFE_DELETE(gScene);
    SAFE_DELETE(gCamera);
    gLog->Close();
    SAFE_DELETE(gLog);
}

void TacticsVictory::CreateComponents()
{
    gProfiler = GetSubsystem<Profiler>();
    gLocalization = GetSubsystem<Localization>();
    gUI = GetSubsystem<UI>();
    gCache = GetSubsystem<ResourceCache>();

    gEngine = GetSubsystem<Engine>();
    gInput = GetSubsystem<Input>();
    gRenderer = GetSubsystem<Renderer>();
    gGraphics = GetSubsystem<Graphics>();

    gScene = new Urho3D::Scene(gContext);
    // Create the Octree component to the scene so that drawable objects can be rendered. Use default volume (-1000, -1000, -1000) to (1000, 1000, 1000)
    gScene->CreateComponent<Octree>();

    gPhysicsWorld = gScene->CreateComponent<PhysicsWorld>();
    gPhysicsWorld->SetGravity(Vector3::ZERO);

    gUIRoot = gUI->GetRoot();

    gScene->CreateComponent<DebugRenderer>();
    gDebugRenderer = gScene->GetComponent<DebugRenderer>();

    gGUI = new GUI();

    gLevel = new Level();

    gAudio = GetSubsystem<Audio>();

    lScene::RegisterObject();
}

void TacticsVictory::RegistrationFactories()
{
    gContext->RegisterFactory<Rotator>();
    gContext->RegisterFactory<Movinator>();
    gContext->RegisterFactory<lImage>();
}

void TacticsVictory::Start()
{
    Application::Start();

    gTime = GetSubsystem<Time>();

    gLog = new Urho3D::Log(gContext);
    gLog->Open("log.txt");
    gLog->SetLevel(Urho3D::LOG_INFO);

    RegistrationFactories();

    CreateComponents();

    gCache->AddResourceDir(gFileSystem->GetProgramDir() + "../TVData");
    gFont = gCache->GetResource<Font>(SET::MENU::FONT::NAME);

    SetWindowTitleAndIcon();
    CreateConsoleAndDebugHud();

    XMLFile *style = gCache->GetResource<XMLFile>("UI/MainStyle.xml");
    gUIRoot->SetDefaultStyle(style);
    
    InitLocalizationSystem();

    gCamera = new lCamera();

    gGUI->Create();

    gFileSelector = new FileSelector(gContext);
    gFileSelector->GetWindow()->SetModal(false);
    gFileSelector->GetWindow()->SetVisible(false);

    SubscribeToEvents();

    CreateNewGame();

    URHO3D_LOGINFOF("time create %f sec", gTime->GetElapsedTime());
}

void TacticsVictory::InitLocalizationSystem()
{
    gLocalization->LoadJSONFile("Strings.json");
    gLocalization->SetLanguage("ru");
}

void TacticsVictory::SubscribeToEvents()
{
    SubscribeToEvent(Urho3D::E_UPDATE, URHO3D_HANDLER(TacticsVictory, HandleUpdate));
    SubscribeToEvent(Urho3D::E_POSTRENDERUPDATE, URHO3D_HANDLER(TacticsVictory, HandlePostRenderUpdate));
    SubscribeToEvent(Urho3D::E_KEYDOWN, URHO3D_HANDLER(TacticsVictory, HandleKeyDown));
    SubscribeToEvent(E_MENU, URHO3D_HANDLER(TacticsVictory, HandleMenuEvent));
    SubscribeToEvent(Urho3D::E_POSTUPDATE, URHO3D_HANDLER(TacticsVictory, HandlePostUpdate));
}

void TacticsVictory::SetWindowTitleAndIcon()
{
    Urho3D::Image* icon = gCache->GetResource<Urho3D::Image>("Textures/TacticsVictoryIcon.png");
    gGraphics->SetWindowIcon(icon);
    gGraphics->SetWindowTitle(L"������� ������");
}

void TacticsVictory::CreateConsoleAndDebugHud()
{
    XMLFile* xmlFile = gCache->GetResource<XMLFile>("UI/ConsoleStyle.xml");

    gEngineConsole = engine_->CreateConsole();
    gEngineConsole->SetDefaultStyle(xmlFile);
    gEngineConsole->GetBackground()->SetOpacity(0.8f);

    gDebugHud = engine_->CreateDebugHud();
    gDebugHud->SetDefaultStyle(xmlFile);
}

void TacticsVictory::CreateNewGame()
{
    scene = new lScene();
    gCamera->SetEnabled(true);
    gGUI->RemoveFromScreen();
    gGuiGame->SetVisible(true);
}

void TacticsVictory::CreateEditorSession()
{
    if(!gEditor)
    {
        gEditor = new Editor(gContext);
    }
    gGUI->RemoveFromScreen();
    gGuiEditor->SetVisible(true);
    gCamera->SetEnabled(true);
    gEditor->Run();
}
