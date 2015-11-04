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
#include "TacticsVictory.h"
#include "Game/Level.h"
#include "GlobalFunctions.h"


#pragma warning(push)
#pragma warning(disable:4100)
DEFINE_APPLICATION_MAIN(TacticsVictory)
#pragma warning(pop)



TacticsVictory::TacticsVictory(UContext* context) :
    Application(context)
{
    gContext = context;
}

void TacticsVictory::Setup()
{
    gSet = new Settings();
    gFileSystem = GetSubsystem<UFileSystem>();
    gSet->Load();

    engineParameters_["WindowTitle"] = GetTypeName();
    engineParameters_["LogName"] = GetSubsystem<UFileSystem>()->GetAppPreferencesDir("urho3d", "logs") + GetTypeName() + ".log";
    engineParameters_["FullScreen"] = false;
    engineParameters_["Headless"] = false;
    engineParameters_["TextureQuality"] = 32;
    engineParameters_["WindowWidth"] = gSet->GetInt(TV_SCREEN_WIDTH);
    engineParameters_["WindowHeight"] = gSet->GetInt(TV_SCREEN_HEIGHT);
}

void TacticsVictory::Stop()
{
    TilePath::RemoveAll();
    SAFE_DELETE(gFileSelector);
    SAFE_DELETE(gTerrain);
    SAFE_DELETE(gLevel);
    SAFE_DELETE(gGUI);
    SAFE_DELETE(gTime);
    UFile file(gContext, "ui.xml", Urho3D::FILE_WRITE);
    LOGINFO("Now save ui");
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
    gLocalization = GetSubsystem<Localization>();
    gUI = GetSubsystem<UI>();
    gCache = GetSubsystem<ResourceCache>();

    gEngine = GetSubsystem<UEngine>();
    gInput = GetSubsystem<Input>();
    gRenderer = GetSubsystem<Renderer>();
    gGraphics = GetSubsystem<Graphics>();

    gScene = new UScene(gContext);
    // Create the Octree component to the scene so that drawable objects can be rendered. Use default volume (-1000, -1000, -1000) to (1000, 1000, 1000)
    gScene->CreateComponent<Octree>();

    gPhysicsWorld = gScene->CreateComponent<PhysicsWorld>();

    gUIRoot = gUI->GetRoot();

    gScene->CreateComponent<UDebugRenderer>();
    gDebugRenderer = gScene->GetComponent<UDebugRenderer>();

    gTime = new Time(gContext);

    gGUI = new GUI();

    gLevel = new Level();

    Scene::RegisterObject();
}

void TacticsVictory::RegistrationFactories()
{
    gContext->RegisterFactory<Rotator>();
    gContext->RegisterFactory<Movinator>();
}

void TacticsVictory::Start()
{
    Application::Start();

    gLog = new ULog(gContext);
    gLog->Open("log.txt");
    gLog->SetLevel(Urho3D::LOG_INFO);

    RegistrationFactories();

    CreateComponents();

    gCache->AddResourceDir(gFileSystem->GetProgramDir() + "../TVData");
    gFont = gCache->GetResource<UFont>(SET::MENU::FONT::NAME);
    //gCache->AddResourceDir(gFileSystem->GetProgramDir() + "TVData");


    SetWindowTitleAndIcon();
    CreateConsoleAndDebugHud();

    XMLFile *style = gCache->GetResource<XMLFile>("UI/MainStyle.xml");
    gUIRoot->SetDefaultStyle(style);
    
    InitLocalizationSystem();

    gCamera = new Camera();

    gGUI->Create();

    gFileSelector = new UFileSelector(gContext);
    gFileSelector->GetWindow()->SetModal(false);
    gFileSelector->GetWindow()->SetVisible(false);

    SubscribeToEvents();
}

void TacticsVictory::InitLocalizationSystem()
{
    gLocalization->LoadJSONFile("Strings.json");
    gLocalization->SetLanguage("ru");
}

void TacticsVictory::SubscribeToEvents()
{
    SubscribeToEvent(Urho3D::E_UPDATE, HANDLER(TacticsVictory, HandleUpdate));
    SubscribeToEvent(Urho3D::E_POSTRENDERUPDATE, HANDLER(TacticsVictory, HandlePostRenderUpdate));
    SubscribeToEvent(Urho3D::E_KEYDOWN, HANDLER(TacticsVictory, HandleKeyDown));
    SubscribeToEvent(E_MENU, HANDLER(TacticsVictory, HandleMenuEvent));
}

void TacticsVictory::SetWindowTitleAndIcon()
{
    UImage* icon = gCache->GetResource<UImage>("Textures/TacticsVictoryIcon.png");
    gGraphics->SetWindowIcon(icon);
    gGraphics->SetWindowTitle(L"Тактика победы");
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
    scene = new Scene();
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
