// 2021/04/02 17:53:03 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Hangar.h"
#include "FileSystem/ConfigurationFile_.h"
#include "Graphics/Renderer_.h"
#include "Graphics/2D/Image_.h"
#include "GUI/Menu/MenuEvents_.h"


#pragma warning(push)
#pragma warning(disable:4100)
URHO3D_DEFINE_APPLICATION_MAIN(Hangar)
#pragma warning(pop)


Hangar::Hangar(Context* context) :
    Application(context)
{
    TheContext = context;
}


void Hangar::Setup()
{
    TheHangar = this;

    OpenLog();

    LogRAW::Create((GetTypeName() + ".log").CString(), true);

    LOGWRITE("Start Hangar");

    GetSubsystems();

    TheSettings.Load("Settings.conf");

    TuneEngineParameters();
}


void Hangar::GetSubsystems()
{
    TheCache = GetSubsystem<ResourceCache>();
    TheEngine = GetSubsystem<Engine>();
    TheFileSystem = GetSubsystem<FileSystem>();
    TheGraphics = GetSubsystem<Graphics>();
    TheLocalization = GetSubsystem<Localization>();
    TheUI = GetSubsystem<UI>();
    TheTime = GetSubsystem<Time>();
    TheInput = GetSubsystem<Input>();
    TheRenderer = GetSubsystem<Renderer>();
}


void Hangar::TuneEngineParameters()
{
    engineParameters_[EP_WINDOW_TITLE] = GetTypeName();
    engineParameters_[EP_LOG_NAME] = GetSubsystem<FileSystem>()->
                                                        GetAppPreferencesDir("urho3d", "logs") + GetTypeName() + ".log";
    engineParameters_[EP_FULL_SCREEN] = false;
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


void Hangar::Start()
{
    GetSubsystems();

    Application::Start();

    SetLocalization();

    TheFont = TheCache->GetResource<Font>(TheSettings.GetString("menu", "font", "name"));

    RegistrationObjects();

    mouse = new Mouse(&TheMouse);

    SetWindowTitleAndIcon();

    CreateConsoleAndDebugHud();

    SubscribeToEvents();

    scene = new SceneC(&TheScene);

    TheScene->CreateComponent<DebugRenderer>(LOCAL);
    TheDebugRenderer = TheScene->GetComponent<DebugRenderer>();

    CreateGUI();

    RendererT::LoadSettings();

    menu = new Menus(&TheMenu);

    ParseArguments();

    TheInput->SetMouseMode(MouseMode::MM_FREE);
}


void Hangar::CreateGUI()
{
    TheUIRoot = TheUI->GetRoot();
    TheUIRoot->SetDefaultStyle(TheCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    gui = new GUI(&TheGUI);
}


void Hangar::Stop()
{
    TheSettings.Unload();

    engine_->DumpResources(true);
    engine_->DumpProfiler();
}


void Hangar::SetLocalization()
{
    TheLocalization->LoadJSONFile("Strings.json");
    TheLocalization->SetLanguage(TheSettings.GetInt("language") == 0 ? "en" : "ru");
}


void Hangar::RegistrationObjects()
{
    CursorT::RegisterObject();
    ImageT::RegisterObject();
    Control::RegisterObject();
}


void Hangar::SubscribeToEvents()
{
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(Hangar, HandlerKeyDown));
    SubscribeToEvent(E_MENU, URHO3D_HANDLER(Hangar, HandlerMenuEvent));
    SubscribeToEvent(E_POSTRENDERUPDATE, URHO3D_HANDLER(Hangar, HandlerPostRenderUpdate));
}


void Hangar::SetWindowTitleAndIcon()
{
    Image *icon = TheCache->GetResource<Image>("Textures/TacticsVictoryIcon.png");
    TheGraphics->SetWindowIcon(icon);

    SetWindowText(FindWindow(NULL, "Battler"), TheSettings.GetInt("language") == 0 ? TEXT("Tactics Victory") :
        TEXT("Тактика Победы"));
}


void Hangar::CreateConsoleAndDebugHud()
{
    XMLFile *xmlFile = TheCache->GetResource<XMLFile>("UI/ConsoleStyle.xml");

    TheEngineConsole = engine_->CreateConsole();
    TheEngineConsole->SetDefaultStyle(xmlFile);
    TheEngineConsole->GetBackground()->SetOpacity(0.8f);

    TheDebugHud = engine_->CreateDebugHud();
    TheDebugHud->SetDefaultStyle(xmlFile);
}


void Hangar::OpenLog()
{
    log = new Log(TheContext);
    log->Open(GetTypeName() + ".log");
    log->SetLevel(LOG_TRACE);
}


void Hangar::ParseArguments()
{

}
