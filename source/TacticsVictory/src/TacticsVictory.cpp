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


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TacticsVictory::TacticsVictory(Context* context) :
    Application(context)
{
    gContext = context;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::Setup()
{
    gSet = new Settings();
    gCache = GetSubsystem<ResourceCache>();
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

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::Stop()
{
    float time = gTime->GetElapsedTime();
    engine_->DumpResources(true);
    //engine_->DumpProfiler();
    TilePath::RemoveAll();
    Rocket::DeleteAll();
    SAFE_DELETE(gScene);
    SAFE_DELETE(scene);
    SAFE_DELETE(gFileSelector);
    SAFE_DELETE(gLevel);
    SAFE_DELETE(gGUI);
    //File file(gContext, "ui.xml", FILE_WRITE);
    //URHO3D_LOGINFO("Now save ui");
    //gUIRoot->SaveXML(file);
    URHO3D_LOGINFO("gSet->Save");
    gSet->Save();
    SAFE_DELETE(gSet);
    URHO3D_LOGINFO("dump");
    URHO3D_LOGINFO("Now destroy gEditor");
    SAFE_DELETE(gEditor);
    URHO3D_LOGINFO("gScene");
    URHO3D_LOGINFO("gCamera");
    SAFE_DELETE(gCamera);    
    URHO3D_LOGINFOF("time Stop() %f sec", gTime->GetElapsedTime() - time);
    gLog->Close();
    SAFE_DELETE(gLog);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::CreateComponents()
{
    gProfiler = GetSubsystem<Profiler>();
    gLocalization = GetSubsystem<Localization>();
    gUI = GetSubsystem<UI>();

    gEngine = GetSubsystem<Engine>();
    gInput = GetSubsystem<Input>();
    gRenderer = GetSubsystem<Renderer>();
    gGraphics = GetSubsystem<Graphics>();

    gScene = new Scene(gContext);
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

    SceneRTS::RegisterObject();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::RegistrationFactories()
{
    gContext->RegisterFactory<Rotator>();
    gContext->RegisterFactory<Movinator>();
    gContext->RegisterFactory<ImageRTS>();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::Start()
{
    gProfiler = GetSubsystem<Profiler>();
    PROFILER_FUNC_ENTER
    Application::Start();

    gTime = GetSubsystem<Time>();

    gLog = new Log(gContext);
    gLog->Open("log.txt");
    gLog->SetLevel(LOG_DEBUG);

    RegistrationFactories();

    CreateComponents();

    gCache->AddResourceDir(gFileSystem->GetProgramDir() + RESOURCES_DIR);
    gFont = gCache->GetResource<Font>(SET::MENU::FONT::NAME);

    SetWindowTitleAndIcon();
    CreateConsoleAndDebugHud();

    XMLFile *style = gCache->GetResource<XMLFile>("UI/MainStyle.xml");
    gUIRoot->SetDefaultStyle(style);
    
    InitLocalizationSystem();

    gCamera = new CameraRTS();

    gLog->SetLevel(LOG_ERROR);
    gGUI->Create();
    gLog->SetLevel(LOG_INFO);

    gFileSelector = new FileSelector(gContext);
    gFileSelector->GetWindow()->SetModal(false);
    gFileSelector->GetWindow()->SetVisible(false);

    SubscribeToEvents();

    CreateNewGame();

    gContext->RegisterSubsystem(new Script(gContext));
    gScript = GetSubsystem<Script>();
    gScript->Execute("Print(\"Hello World!\");");

    PROFILER_FUNC_LEAVE;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::InitLocalizationSystem()
{
    gLocalization->LoadJSONFile("Strings.json");
    gLocalization->SetLanguage("ru");
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::SubscribeToEvents()
{
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(TacticsVictory, HandleUpdate));
    SubscribeToEvent(E_POSTRENDERUPDATE, URHO3D_HANDLER(TacticsVictory, HandlePostRenderUpdate));
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(TacticsVictory, HandleKeyDown));
    SubscribeToEvent(E_MENU, URHO3D_HANDLER(TacticsVictory, HandleMenuEvent));
    SubscribeToEvent(E_POSTUPDATE, URHO3D_HANDLER(TacticsVictory, HandlePostUpdate));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::SetWindowTitleAndIcon()
{
    Image* icon = gCache->GetResource<Image>("Textures/TacticsVictoryIcon.png");
    gGraphics->SetWindowIcon(icon);
    gGraphics->SetWindowTitle(L"Тактика победы");
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::CreateConsoleAndDebugHud()
{
    XMLFile* xmlFile = gCache->GetResource<XMLFile>("UI/ConsoleStyle.xml");

    gEngineConsole = engine_->CreateConsole();
    gEngineConsole->SetDefaultStyle(xmlFile);
    gEngineConsole->GetBackground()->SetOpacity(0.8f);

    gDebugHud = engine_->CreateDebugHud();
    gDebugHud->SetDefaultStyle(xmlFile);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::CreateNewGame()
{
    scene = new SceneRTS();
    gCamera->SetEnabled(true);
    gGUI->RemoveFromScreen();
    gGuiGame->SetVisible(true);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
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
