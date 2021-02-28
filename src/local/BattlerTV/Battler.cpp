// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Battler.h"
#include "Editor/Editor.h"
#include "Game/Logic/Rotator_.h"
#include "Game/Logic/SunEngine_.h"
#include "Game/Path/TilePath.h"
#include "Graphics/2D/Image.h"
#include "Graphics/3D/TileSelected.h"
#include "GUI/Cursor.h"
#include "GUI/GUI.h"
#include "GUI/GuiEditor/GuiEditor.h"
#include "GUI/Menu/MenuEvents.h"
#include "GUI/Menu/Menu.h"
#include "Input/Mouse.h"
#include "Network/ServerC.h"
#include "Scene/Level_.h"
#include "Scene/SceneC.h"
#include "Scene/Cameras/Camera.h"
#include "Scene/Objects/GameObject_.h"
#include "Utils/Log_.h"
#include "Utils/Settings.h"
#include "Utils/SettingsTypes.h"


#pragma warning(push)
#pragma warning(disable:4100)
URHO3D_DEFINE_APPLICATION_MAIN(Battler)
#pragma warning(pop)


Battler::Battler(Context* context) :
    Application(context)
{
    TheContext = context;
}


void Battler::Setup()
{
    TheBattler = this;

    GetSubsystems();

    TheSet = new Settings();

    TheSet->Load();

    TuneEngineParameters();
}


void Battler::GetSubsystems()
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
    TheNetwork = GetSubsystem<Network>();

    CreateScriptSystem();
}


void Battler::TuneEngineParameters()
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

    TheCache->AddResourceDir(RESOURCES_DIR);
}


void Battler::Start()
{
    OpenLog();

    PROFILER_FUNC_ENTER();

    GetSubsystems();

    Application::Start();

    SetLocalization();
    TheFont = TheCache->GetResource<Font>(SET::MENU::FONT::NAME);

    RegistrationComponets();

    TheMouse = new Mouse();

    SetWindowTitleAndIcon();

    CreateConsoleAndDebugHud();

    SubscribeToEvents();

    TheServer = new ServerC();

    TheServer->Connect(SERVER_ADDRESS, SERVER_PORT);

    TheScene = new SceneC();

    TheScene->CreateComponent<DebugRenderer>(LOCAL);
    TheDebugRenderer = TheScene->GetComponent<DebugRenderer>();

    CreateGUI();

    LOGINFO("Загружаю настройки");
    TheMenu = new MenuT();
    TheFileSelector = new FileSelector(TheContext);
    TheFileSelector->GetWindow()->SetModal(false);
    TheFileSelector->GetWindow()->SetVisible(false);

    PROFILER_FUNC_LEAVE();
}


void Battler::CreateGUI()
{
    TheUIRoot = TheUI->GetRoot();
    TheUIRoot->SetDefaultStyle(TheCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    TheGUI = new GUI();
}


void Battler::Stop()
{
    engine_->DumpResources(true);
    engine_->DumpProfiler();

    TilePath::RemoveAll();

    delete TheScene;
    delete TheServer;
    delete TheMouse;
    delete ThePathIndicator;
    delete TheFileSelector;
    delete TheLevel;
    delete TheMenu;
    delete TheGUI;
    delete TheSet;
    delete TheEditor;
    delete TheLog;
}


void Battler::SetLocalization()
{
    TheLocalization->LoadJSONFile("Strings.json");
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


void Battler::CreateScriptSystem()
{
    TheContext->RegisterSubsystem(new Script(TheContext));
    TheScript = GetSubsystem<Script>();
    TheScript->GetScriptEngine()->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);
}


void Battler::RegistrationComponets()
{
    CameraT::RegisterObject();
    CursorT::RegisterObject();
    TImage::RegisterObject();
    SunEngine::RegisterObject();
    Rotator::RegisterObject();
    WaveAlgorithm::RegisterObject();
    SceneT::RegisterObject();
    TileSelected::RegisterObject();

    GameObject::RegisterObject();
}


void Battler::SubscribeToEvents()
{
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(Battler, HandleKeyDown));
    SubscribeToEvent(E_MENU, URHO3D_HANDLER(Battler, HandleMenuEvent));
    SubscribeToEvent(E_POSTRENDERUPDATE, URHO3D_HANDLER(Battler, HandlePostRenderUpdate));
}


void Battler::SetWindowTitleAndIcon()
{
    Image *icon = TheCache->GetResource<Image>("Textures/TacticsVictoryIcon.png");
    TheGraphics->SetWindowIcon(icon);
    TheGraphics->SetWindowTitle("Тактика победы");
}


void Battler::CreateConsoleAndDebugHud()
{
    XMLFile *xmlFile = TheCache->GetResource<XMLFile>("UI/ConsoleStyle.xml");

    TheEngineConsole = engine_->CreateConsole();
    TheEngineConsole->SetDefaultStyle(xmlFile);
    TheEngineConsole->GetBackground()->SetOpacity(0.8f);

    TheDebugHud = engine_->CreateDebugHud();
    TheDebugHud->SetDefaultStyle(xmlFile);
}


void Battler::CreateEditorSession()
{
    if(!TheEditor)
    {
        TheEditor = new Editor();
    }
    TheGuiEditor->SetVisible(true);
    TheCamera->SetEnabled(true);
    TheEditor->Run();
}


void Battler::OpenLog()
{
    TheLog = new LogT();
    TheLog->Open(GetTypeName() + ".log");
    TheLog->SetLevel(LOG_DEBUG);
}
