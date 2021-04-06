// 2021/04/02 17:53:03 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Client.h"
#include "GUI/Menu/Menu.h"


#pragma warning(push)
#pragma warning(disable:4100)
URHO3D_DEFINE_APPLICATION_MAIN(Client)
#pragma warning(pop)


Client::Client(Context* context) :
    Application(context)
{
    TheContext = context;
}


void Client::Setup()
{
    OpenLog();

    LogRAW::Create("Client.log", true);

    LOGWRITE("Start Client");

    TheConfig.Load("Client.conf");

    TheClient = this;

    GetSubsystems();

    TheSettings.Load("Settings.conf");

    TuneEngineParameters();
}


void Client::GetSubsystems()
{
    TheCache = GetSubsystem<ResourceCache>();
    TheEngine = GetSubsystem<Engine>();
    TheFileSystem = GetSubsystem<FileSystem>();
    TheGraphics = GetSubsystem<Graphics>();
    TheLocalization = GetSubsystem<Localization>();
    TheUI = GetSubsystem<UI>();
    TheTime = GetSubsystem<Time>();
}


void Client::TuneEngineParameters()
{
    engineParameters_[EP_WINDOW_TITLE] = GetTypeName();
    engineParameters_[EP_LOG_NAME] = GetSubsystem<FileSystem>()->
                                                        GetAppPreferencesDir("urho3d", "logs") + GetTypeName() + ".log";
    engineParameters_[EP_FULL_SCREEN] = false;
    engineParameters_[EP_TEXTURE_QUALITY] = 32;
    engineParameters_[EP_WINDOW_WIDTH] = TheSettings.GetInt("client", "screen", "width");
    engineParameters_[EP_WINDOW_HEIGHT] = TheSettings.GetInt("client", "screen", "height");
    engineParameters_[EP_HEADLESS] = false;

    if (!engineParameters_.Contains(EP_RESOURCE_PREFIX_PATHS))
#ifdef DEBUG
        engineParameters_[EP_RESOURCE_PREFIX_PATHS] = ";../../../../../../out/debug";
#else
        engineParameters_[EP_RESOURCE_PREFIX_PATHS] = ";../../../../../../out/release";
#endif

    TheCache->AddResourceDir(RESOURCES_DIR);
}


void Client::Start()
{
    GetSubsystems();

    Application::Start();

    SetLocalization();
    TheFont = TheCache->GetResource<Font>(TheSettings.GetString("menu", "font", "name"));

    RegistrationObjects();

    mouse = new Mouse(&TheMouse);

    CreateConsoleAndDebugHud();

    SubscribeToEvents();

    TheScene = new Scene(TheContext);

    CreateGUI();

    menu = new Menus(&TheMenu);

    SetWindowTitleAndIcon();

    ParseArguments();
}


void Client::ParseArguments()
{
    const Vector<String> &arguments = GetArguments();

    if (arguments.Size() != 0)
    {
        TheMasterServer.Connect(arguments[0].CString());
    }
    else
    {
        LOGWARNINGF("Not specified address master server");
        TheGUI->AppendWarning("Not specified address master server");
    }
}


void Client::Stop()
{
    engine_->DumpResources(true);
    engine_->DumpProfiler();

    delete TheScene;
}


void Client::CreateGUI()
{
    TheUIRoot = TheUI->GetRoot();
    TheUIRoot->SetDefaultStyle(TheCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    gui = new GUI(&TheGUI);
}


void Client::SetLocalization()
{
    TheLocalization->LoadJSONFile("Strings.json");
    TheLocalization->SetLanguage(TheSettings.GetInt("language") == 0 ? "en" : "ru");
}


void Client::RegistrationObjects()
{
    CameraT::RegisterObject();
    CursorT::RegisterObject();
    ImageT::RegisterObject();
}


void Client::SubscribeToEvents()
{
}


void Client::SetWindowTitleAndIcon()
{
    Image *icon = TheCache->GetResource<Image>("Textures/TacticsVictoryIcon.png");
    TheGraphics->SetWindowIcon(icon);

    SetWindowText(FindWindow(NULL, "Client"), TheLocalization->GetLanguage() == "en" ? TEXT("Tactics Victory") :
                                                                                       TEXT("Тактика Победы"));
}


void Client::CreateConsoleAndDebugHud()
{
}


void Client::OpenLog()
{
    log = new Log(TheContext);
    log->Open(GetTypeName() + ".log");
    log->SetLevel(LOG_DEBUG);
}
