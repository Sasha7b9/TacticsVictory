// 2021/04/02 17:53:03 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Editor.h"
#include "GUI/Menu/Menu.h"


#pragma warning(push)
#pragma warning(disable:4100)
URHO3D_DEFINE_APPLICATION_MAIN(Editor)
#pragma warning(pop)


Editor::Editor(Context* context) :
    Application(context)
{
    TheContext = context;
}


void Editor::Setup()
{
    OpenLog();

    LogRAW::Create((GetTypeName() + ".log").CString(), true);

    LOGWRITE("Start Client");

    const Vector<String> &arguments = GetArguments();

    TheConfig.Load("Client.conf");

    TheClient = this;

    String address_master = DEFAULT_MASTER_SERVER_ADDRESS;

    if (arguments.Size() == 0)
    {
        LOGWARNINGF("Not specified address master server. Default is %s", DEFAULT_MASTER_SERVER_ADDRESS);
    }
    else
    {
        address_master = String(arguments[0]);
    }

    GetSubsystems();

    TheSettings.Load("Settings.conf");

    TuneEngineParameters();
}


void Editor::GetSubsystems()
{
    TheCache = GetSubsystem<ResourceCache>();
    TheEngine = GetSubsystem<Engine>();
    TheFileSystem = GetSubsystem<FileSystem>();
    TheGraphics = GetSubsystem<Graphics>();
    TheLocalization = GetSubsystem<Localization>();
    TheUI = GetSubsystem<UI>();
}


void Editor::TuneEngineParameters()
{
    engineParameters_[EP_WINDOW_TITLE] = GetTypeName();
    engineParameters_[EP_LOG_NAME] = GetSubsystem<FileSystem>()->
                                                        GetAppPreferencesDir("urho3d", "logs") + GetTypeName() + ".log";
    engineParameters_[EP_FULL_SCREEN] = false;
    engineParameters_[EP_TEXTURE_QUALITY] = 32;
//    engineParameters_[EP_WINDOW_WIDTH] = TheSettings.GetInt("screen", "width");
//    engineParameters_[EP_WINDOW_HEIGHT] = TheSettings.GetInt("screen", "height");
    engineParameters_[EP_HEADLESS] = false;

    if (!engineParameters_.Contains(EP_RESOURCE_PREFIX_PATHS))
#ifdef DEBUG
        engineParameters_[EP_RESOURCE_PREFIX_PATHS] = ";../../../../../../out/debug";
#else
        engineParameters_[EP_RESOURCE_PREFIX_PATHS] = ";../../../../../../out/release";
#endif

    TheCache->AddResourceDir(RESOURCES_DIR);
}


void Editor::Start()
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

    TheScene = new Scene(TheContext);

    CreateGUI();

    ::Menu::Create();
}


void Editor::Stop()
{
    engine_->DumpResources(true);
    engine_->DumpProfiler();

    delete TheScene;
}


void Editor::CreateGUI()
{
    TheUIRoot = TheUI->GetRoot();
    TheUIRoot->SetDefaultStyle(TheCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    gui = new GUI(&TheGUI);
}


void Editor::SetLocalization()
{
    TheLocalization->LoadJSONFile("Strings.json");
    TheLocalization->SetLanguage("ru");
}


void Editor::RegistrationObjects()
{
    CameraT::RegisterObject();
    CursorT::RegisterObject();
    ImageT::RegisterObject();
}


void Editor::SubscribeToEvents()
{
}


void Editor::SetWindowTitleAndIcon()
{
}


void Editor::CreateConsoleAndDebugHud()
{
}


void Editor::OpenLog()
{
    log = new Log(TheContext);
    log->Open(GetTypeName() + ".log");
    log->SetLevel(LOG_DEBUG);
}
