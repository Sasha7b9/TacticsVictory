// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "TTacticsVictory.h"
#include "Editor/TEditor.h"
#include "Game/Logic/_TMovinator.h"
#include "Game/Logic/_TRotator.h"
#include "Game/Path/TTilePath.h"
#include "Graphics/2D/TImage.h"
#include "GUI/TGUI.h"
#include "GUI/GuiEditor/TGuiEditor.h"
#include "GUI/Menu/TMenuEvents.h"
#include "GUI/Menu/TMenu.h"
#include "Scene/_TLevel.h"
#include "Scene/TCScene.h"
#include "Scene/Cameras/TCamera.h"
#include "Scene/Objects/Ammo/Rocket/_TRocket.h"
#include "Scene/Objects/Buildings/_TMilitaryPlant.h"
#include "Scene/Objects/Units/_TTank.h"
#include "Scene/Objects/Units/Logic/_TTranslator.h"
#include "Scene/Objects/Weapons/_TWeaponObject.h"
#include "Utils/TCLog.h"


#pragma warning(push)
#pragma warning(disable:4100)
URHO3D_DEFINE_APPLICATION_MAIN(TacticsVictory)
#pragma warning(pop)


TacticsVictory::TacticsVictory(Context* context) :
    Application(context)
{
    TheContext = context;
}


void TacticsVictory::Setup()
{
    TheTacticsVictory = this;

    GetSubsystems();

    OpenLog();
    TheSet = new Settings();
    TheSet->Load();

    TuneEngineParameters();
}


void TacticsVictory::GetSubsystems()
{
    TheCache = GetSubsystem<ResourceCache>();
    TheFileSystem = GetSubsystem<FileSystem>();
    TheTime = GetSubsystem<Time>();
    TheProfiler = GetSubsystem<Profiler>();
    TheEngine = GetSubsystem<Engine>();
    TheGraphics = GetSubsystem<Graphics>();
    TheRenderer = GetSubsystem<Renderer>();
    TheAudio = GetSubsystem<Audio>();
    TheUI = GetSubsystem<UI>();
    TheInput = GetSubsystem<Input>();
    TheLocalization = GetSubsystem<Localization>();

    CreateScriptSystem();
}


void TacticsVictory::TuneEngineParameters()
{
    engineParameters_[EP_WINDOW_TITLE] = GetTypeName();
    engineParameters_[EP_LOG_NAME] = GetSubsystem<FileSystem>()->
                                                        GetAppPreferencesDir("urho3d", "logs") + GetTypeName() + ".log";
    engineParameters_[EP_FULL_SCREEN] = false;
    engineParameters_[EP_TEXTURE_QUALITY] = 32; //-V112
    engineParameters_[EP_WINDOW_WIDTH] = TheSet->GetInt(TV_SCREEN_WIDTH);
    engineParameters_[EP_WINDOW_HEIGHT] = TheSet->GetInt(TV_SCREEN_HEIGHT);
    engineParameters_[EP_HEADLESS] = false;

    if (!engineParameters_.Contains(EP_RESOURCE_PREFIX_PATHS))
#ifdef DEBUG
        engineParameters_[EP_RESOURCE_PREFIX_PATHS] = ";../../../../../../out/debug";
#else
        engineParameters_[EP_RESOURCE_PREFIX_PATHS] = ";../../../../../../out/release";
#endif

    TheCache->AddResourceDir("TVData");
}


void TacticsVictory::Start()
{
    PROFILER_FUNC_ENTER();

    GetSubsystems();

    Application::Start();

    SetLocalization();
    TheFont = TheCache->GetResource<Font>(SET::MENU::FONT::NAME);

    RegistrationComponets();

    CreateScene();

    TheCamera = TCamera::Create(TheScene->scene);

    SetWindowTitleAndIcon();

    CreateConsoleAndDebugHud();

    TheScene->scene->CreateComponent<DebugRenderer>();
    TheDebugRenderer = TheScene->scene->GetComponent<DebugRenderer>();

    CreateGUI();

    LOGINFO("Загружаю настройки");
    TheMenu = new TMenu();
    TheFileSelector = new FileSelector(TheContext);
    TheFileSelector->GetWindow()->SetModal(false);
    TheFileSelector->GetWindow()->SetVisible(false);

    TheLevel = new Level();

    SubscribeToEvents();

    PROFILER_FUNC_LEAVE();
}


void TacticsVictory::CreateGUI()
{
    TheUIRoot = TheUI->GetRoot();
    TheUIRoot->SetDefaultStyle(TheCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    TheGUI = new GUI();
}


void TacticsVictory::CreateScene()
{
    PROFILER_FUNC_ENTER();

    TheScene = new CScene();

    ThePhysicsWorld = TheScene->scene->CreateComponent<PhysicsWorld>();
    ThePhysicsWorld->SetGravity(Vector3::ZERO);  

    TheScene->Create();

    PROFILER_FUNC_LEAVE();
}


void TacticsVictory::Stop()
{
    engine_->DumpResources(true);
    engine_->DumpProfiler();

    TilePath::RemoveAll();
    Rocket::DeleteAll();

    delete TheScene;
    delete TheFileSelector;
    delete TheLevel;
    delete TheMenu;
    delete TheGUI;
    delete TheSet;
    delete TheEditor;
    delete TheCamera;
    delete TheLog;
}


void TacticsVictory::SetLocalization()
{
    TheLocalization->LoadJSONFile("TVData/Strings.json");
    TheLocalization->SetLanguage("ru");
}


static void MessageCallback(const asSMessageInfo *msg, void *)
{
    const char *type = "AS ERROR ";
    if (msg->type == asMSGTYPE_WARNING)
    {
        type = "AS WARN ";
    }
    else if (msg->type == asMSGTYPE_INFORMATION)
    {
        type = "AS INFO ";
    }

    LOGINFOF("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message); //-V111
}


void TacticsVictory::CreateScriptSystem()
{
    TheContext->RegisterSubsystem(new Script(TheContext));
    TheScript = GetSubsystem<Script>();
    TheScript->GetScriptEngine()->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);
}


void TacticsVictory::RegistrationComponets()
{
    TImage::RegisterObject();
    Movinator::RegisterObject();
    Rotator::RegisterObject();

    RocketLauncher::RegisterObject();
    Rocket::RegisterObject();

    Translator::RegisterObject();
    WaveAlgorithm::RegisterObject();
    Tank::RegisterObject();

    MilitaryPlant::RegisterObject();

    TScene::RegisterObject();
}


void TacticsVictory::SubscribeToEvents()
{
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(TacticsVictory, HandleKeyDown));
    SubscribeToEvent(E_MENU, URHO3D_HANDLER(TacticsVictory, HandleMenuEvent));
    SubscribeToEvent(E_POSTRENDERUPDATE, URHO3D_HANDLER(TacticsVictory, HandlePostRenderUpdate));

    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(TacticsVictory, HandleUpdate));
    SubscribeToEvent(E_POSTUPDATE, URHO3D_HANDLER(TacticsVictory, HandlePostUpdate));
}


void TacticsVictory::SetWindowTitleAndIcon()
{
    Image *icon = TheCache->GetResource<Image>("Textures/TacticsVictoryIcon.png");
    TheGraphics->SetWindowIcon(icon);
    TheGraphics->SetWindowTitle("Тактика победы");
}


void TacticsVictory::CreateConsoleAndDebugHud()
{
    XMLFile *xmlFile = TheCache->GetResource<XMLFile>("UI/ConsoleStyle.xml");

    TheEngineConsole = engine_->CreateConsole();
    TheEngineConsole->SetDefaultStyle(xmlFile);
    TheEngineConsole->GetBackground()->SetOpacity(0.8f);

    TheDebugHud = engine_->CreateDebugHud();
    TheDebugHud->SetDefaultStyle(xmlFile);
}


void TacticsVictory::CreateEditorSession()
{
    if(!TheEditor)
    {
        TheEditor = new Editor();
    }
    TheGuiEditor->SetVisible(true);
    TheCamera->SetEnabled(true);
    TheEditor->Run();
}


void TacticsVictory::OpenLog()
{
    TheLog = new CLog();
    char buffer[50];
    srand(static_cast<uint>(time(static_cast<time_t*>(0)))); //-V202

    sprintf_s(buffer, 50, "TV.log");

    TheLog->Open(buffer);
    TheLog->SetLevel(LOG_DEBUG);
}
