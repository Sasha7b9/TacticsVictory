// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Battler.h"
#include "Editor/Editor.h"
#include "FileSystem/ConfigurationFile_v.h"
#include "Game/Logic/Rotator_.h"
#include "Game/Logic/SunEngine_.h"
#include "Game/Path/TilePath.h"
#include "Graphics/Renderer_.h"
#include "Graphics/2D/Image_.h"
#include "Graphics/3D/TileSelected.h"
#include "GUi/Cursor_.h"
#include "GUI/GUI.h"
#include "GUI/GuiEditor/GuiEditor.h"
#include "GUI/Menu/Menu.h"
#include "GUI/Menu/MenuEvents_.h"
#include "Input/Mouse_v.h"
#include "Network/ServerC.h"
#include "Scene/SceneC.h"
#include "Scene/Cameras/Camera_.h"
#include "Scene/Objects/Units/Air/AirPlane/AirPlane_.h"
#include "Scene/Objects/Units/Ground/Tank/Tank_.h"


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

    OpenLog();

    LogRAW::Create("Battler.log", true);

    LOGWRITE("Start Battler");

    GetSubsystems();

    TheSettings.Load("Settings.conf");

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
    engineParameters_[EP_TEXTURE_QUALITY] = 32;
    engineParameters_[EP_HEADLESS] = false;

    if (TheSettings.GetBool("full_screen"))
    {
        engineParameters_[EP_FULL_SCREEN] = true;
    }
    else
    {
        engineParameters_[EP_FULL_SCREEN] = false;
        engineParameters_[EP_WINDOW_WIDTH] = TheSettings.GetInt("screen", "width");
        engineParameters_[EP_WINDOW_HEIGHT] = TheSettings.GetInt("screen", "height");
    }

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
    GetSubsystems();

    Application::Start();

    SetLocalization();
    TheFont = TheCache->GetResource<Font>(TheSettings.GetString("menu", "font", "name"));

    RegistrationObjects();

    mouse = new Mouse(&TheMouse, TheContext);

    SetWindowTitleAndIcon();

    CreateConsoleAndDebugHud();

    SubscribeToEvents();

    server = new ServerC(&TheServer);

//    TheServer->Connect(SERVER_ADDRESS, SERVER_PORT);

    scene = new SceneC(&TheScene);

    TheScene->CreateComponent<DebugRenderer>(LOCAL);
    TheDebugRenderer = TheScene->GetComponent<DebugRenderer>();

    CreateGUI();

    RendererT::LoadSettings();

    menu = new Menus(&TheMenu);

    TheFileSelector = new FileSelector(TheContext);
    TheFileSelector->GetWindow()->SetModal(false);
    TheFileSelector->GetWindow()->SetVisible(false);
}


void Battler::CreateGUI()
{
    TheUIRoot = TheUI->GetRoot();
    TheUIRoot->SetDefaultStyle(TheCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    gui = new GUI(&TheGUI);
}


void Battler::Stop()
{
    engine_->DumpResources(true);
    engine_->DumpProfiler();

    TilePath::RemoveAll();

    delete ThePathIndicator;
    delete TheFileSelector;
}


void Battler::SetLocalization()
{
    TheLocalization->LoadJSONFile("Strings.json");
    TheLocalization->SetLanguage(TheSettings.GetInt("language") == 0 ? "en" : "ru");
}


//static void MessageCallback(const asSMessageInfo *msg, void *)
//{
//    const char *type = "AS ERROR ";
//    if (msg->type == asMSGTYPE_WARNING)
//    {
//        type = "AS WARN ";
//    }
//    else if (msg->type == asMSGTYPE_INFORMATION)
//    {
//        type = "AS INFO ";
//    }
//
//    LOGWRITEF("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message); //-V111
//}


void Battler::CreateScriptSystem()
{
//    TheContext->RegisterSubsystem(new Script(TheContext));
//    TheScript = GetSubsystem<Script>();
//    TheScript->GetScriptEngine()->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);
}


void Battler::RegistrationObjects()
{
    CameraT::RegisterObject();
    CursorT::RegisterObject();
    ImageT::RegisterObject();
    SunEngine::RegisterObject();
    Rotator::RegisterObject();
    WaveAlgorithm::RegisterObject();
    TileSelected::RegisterObject();
    AirPlane::RegisterObject();
    Tank::RegisterObject();
}


void Battler::SubscribeToEvents()
{
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(Battler, HandlerKeyDown));
    SubscribeToEvent(E_MENU, URHO3D_HANDLER(Battler, HandlerMenuEvent));
    SubscribeToEvent(E_POSTRENDERUPDATE, URHO3D_HANDLER(Battler, HandlerPostRenderUpdate));
}


void Battler::SetWindowTitleAndIcon()
{
    Image *icon = TheCache->GetResource<Image>("Textures/TacticsVictoryIcon.png");
    TheGraphics->SetWindowIcon(icon);

    SetWindowText(FindWindow(NULL, "Battler"), TheSettings.GetInt("language") == 0 ? TEXT("Tactics Victory") :
                                                                                     TEXT("Тактика Победы"));
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
    if(!editor)
    {
        editor = new Editor(&TheEditor);
    }
    TheGuiEditor->SetVisible(true);
    TheCamera->SetEnabled(true);
    TheEditor->Run();
}


void Battler::OpenLog()
{
    log = new Log(TheContext);
    log->Open(GetTypeName() + ".log");
    log->SetLevel(LOG_TRACE);
}
