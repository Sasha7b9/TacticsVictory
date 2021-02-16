// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


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
    ParseArguments(GetArguments());

    TheTacticsVictory = this;
    TheSet = new Settings();
    TheCache = GetSubsystem<ResourceCache>();
    TheFileSystem = GetSubsystem<FileSystem>();
    OpenLog();
//    LOGINFO("Загружаю настройки");
    TheSet->Load();
    //LOGINFO("Загрузка настроек закончена");

    engineParameters_[EP_WINDOW_TITLE] = GetTypeName();
    engineParameters_[EP_LOG_NAME] = GetSubsystem<FileSystem>()->GetAppPreferencesDir("urho3d", "logs") + GetTypeName() + ".log";
    engineParameters_[EP_FULL_SCREEN] = false;
    engineParameters_[EP_TEXTURE_QUALITY] = 32; //-V112
    engineParameters_[EP_WINDOW_WIDTH] = TheSet->GetInt(TV_SCREEN_WIDTH);
    engineParameters_[EP_WINDOW_HEIGHT] = TheSet->GetInt(TV_SCREEN_HEIGHT);
    engineParameters_[EP_HEADLESS] = MODE_SERVER;

    if (!engineParameters_.Contains(EP_RESOURCE_PREFIX_PATHS))
#ifdef DEBUG
        engineParameters_[EP_RESOURCE_PREFIX_PATHS] = ";../../../../../../out/debug;../../../../../../out/debug/TVData";
#else
        engineParameters_[EP_RESOURCE_PREFIX_PATHS] = ";../../../../../../out/release";
#endif
}


void Battler::Stop()
{
    engine_->DumpResources(true);
    //engine_->DumpProfiler();
    TilePath::RemoveAll();
    Rocket::DeleteAll();
    SAFE_DELETE(TheScene); //-V809
    SAFE_DELETE(scene); //-V809
    SAFE_DELETE(TheFileSelector); //-V809
    SAFE_DELETE(TheLevel); //-V809
    SAFE_DELETE(TheMenu); //-V809
    SAFE_DELETE(TheGUI); //-V809
    //File file(TheContext, "ui.xml", FILE_WRITE);
    //URHO3D_LOGINFO("Now save ui");
    //TheUIRoot->SaveXML(file);
    TheSet->Save();
    SAFE_DELETE(TheSet); //-V809
    SAFE_DELETE(TheEditor); //-V809
    SAFE_DELETE(TheCamera);     //-V809
    TheLog->Close();
    SAFE_DELETE(TheLog); //-V809
}


void MessageCallback(const asSMessageInfo *msg, void *)
{
    const char *type = "AS ERROR ";
    if(msg->type == asMSGTYPE_WARNING)
        type = "AS WARN ";
    else if(msg->type == asMSGTYPE_INFORMATION)
        type = "AS INFO ";

    LOGINFOF("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message); //-V111
}


void Battler::Start()
{
    TheProfiler = GetSubsystem<Profiler>();
    PROFILER_FUNC_ENTER
    Application::Start();
    FillNetworkFunctions();
    TheCache->AddResourceDir("TVData");
    SetLocalization();
    TheTime = GetSubsystem<Time>();
    TheFont = TheCache->GetResource<Font>(SET::MENU::FONT::NAME);
    TheProfiler = GetSubsystem<Profiler>();
    TheEngine = GetSubsystem<Engine>();
    TheGraphics = GetSubsystem<Graphics>();
    TheScene = new Scene(TheContext);
    TheScene->CreateComponent<Octree>();
    ThePhysicsWorld = TheScene->CreateComponent<PhysicsWorld>();
    ThePhysicsWorld->SetGravity(Vector3::ZERO);
    TheScene->CreateComponent<DebugRenderer>();

    if (MODE_SERVER)
    {
        CreateScriptSystem();
    }
    else
    {
        SetWindowTitleAndIcon();
        CreateConsoleAndDebugHud();
        TheUI = GetSubsystem<UI>();
        TheInput = GetSubsystem<Input>();
        TheAudio = GetSubsystem<Audio>();
        TheRenderer = GetSubsystem<Renderer>();
        TheCamera = new CameraRTS();
        TheDebugRenderer = TheScene->GetComponent<DebugRenderer>();
        TheUIRoot = TheUI->GetRoot();
        TheUIRoot->SetDefaultStyle(TheCache->GetResource<XMLFile>("UI/MainStyle.xml"));
        TheGUI = new GUI();
        LOGINFO("Загружаю настройки");
        TheMenu = new MenuRTS();
        TheFileSelector = new FileSelector(TheContext);
        TheFileSelector->GetWindow()->SetModal(false);
        TheFileSelector->GetWindow()->SetVisible(false);
    }
    
    RegistrationComponets();

    TheLevel = new Level();

    if (MODE_CLIENT)
    {
        StartClient(address, port);
    }
    else if (MODE_SERVER)
    {
        StartServer(port);
    }

    SubscribeToEvents();

    PROFILER_FUNC_LEAVE;
}


void Battler::SetLocalization()
{
    TheLocalization = GetSubsystem<Localization>();
    TheLocalization->LoadJSONFile("TVData/Strings.json");
    TheLocalization->SetLanguage("ru");
}


void Battler::CreateScriptSystem()
{
    TheContext->RegisterSubsystem(new Script(TheContext));
    TheScript = GetSubsystem<Script>();
    TheScript->GetScriptEngine()->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);
}


void Battler::StartServer(uint16 port_)
{
    if (port_)
    {
        port = port_;
    }

    if (port)
    {
        scene = new SceneRTS(TheContext, SceneRTS::Mode_Server);
        scene->Create();
    }
    else
    {
        LOGERROR("Can not start server on null port");
    }
    
}


void Battler::StopServer()
{

}


void Battler::StartClient(const String &, uint16)
{

}


void Battler::StopClient()
{

}


void Battler::ParseArguments(const Vector<String> &arguments)
{
    /*
        1. нет аргументов - просто запуск
        2. аргументы -port:XX - запуск сервера на порту XX
        3. аргументы -address:XX.XX.XX.XX -port:XX - запуск оболочки и коннект к серверу на XX.XX.XX.XX:XX
    */

    if (GF::GetAddressPort(arguments, address, port))
    {
        TheMode = address.Empty() ? ModeApp_Server : ModeApp_Client;
    }
}


void Battler::RegistrationComponets()
{
    TheContext->RegisterFactory<Rotator>();
    TheContext->RegisterFactory<Movinator>();
    TheContext->RegisterFactory<ImageRTS>();

    SceneRTS::RegisterObject();

    if(MODE_SERVER)
    {
        RocketLauncher::RegisterInAS();
        Translator::RegisterInAS();
        WaveAlgorithm::RegisterInAS();
        Tank::RegisterInAS();
    }
}


void Battler::SubscribeToEvents()
{
    if (MODE_SERVER)
    {

    }
    else
    {
        SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(Battler, HandleKeyDown));
        SubscribeToEvent(E_MENU, URHO3D_HANDLER(Battler, HandleMenuEvent));
        SubscribeToEvent(E_POSTRENDERUPDATE, URHO3D_HANDLER(Battler, HandlePostRenderUpdate));
    }
    
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(Battler, HandleUpdate));
    SubscribeToEvent(E_POSTUPDATE, URHO3D_HANDLER(Battler, HandlePostUpdate));
}


void Battler::SetWindowTitleAndIcon()
{
    if (MODE_CLIENT)
    {
        Image* icon = TheCache->GetResource<Image>("Textures/TacticsVictoryIcon.png");
        TheGraphics->SetWindowIcon(icon);
        TheGraphics->SetWindowTitle("Тактика победы");
    }
}


void Battler::CreateConsoleAndDebugHud()
{
    if (MODE_CLIENT)
    {
        XMLFile* xmlFile = TheCache->GetResource<XMLFile>("UI/ConsoleStyle.xml");

        TheEngineConsole = engine_->CreateConsole();
        TheEngineConsole->SetDefaultStyle(xmlFile);
        TheEngineConsole->GetBackground()->SetOpacity(0.8f);

        TheDebugHud = engine_->CreateDebugHud();
        TheDebugHud->SetDefaultStyle(xmlFile);
    }
}


void Battler::CreateEditorSession()
{
    if(!TheEditor)
    {
        TheEditor = new Editor(TheContext);
    }
    TheGuiEditor->SetVisible(true);
    TheCamera->SetEnabled(true);
    TheEditor->Run();
}


void Battler::FillNetworkFunctions()
{
#define ADD_NETWORK_FUNCTION(name) networkFunctions[name] = FUNC_##name

    ADD_NETWORK_FUNCTION(MSG_REQUEST_LANDSCAPE);
    ADD_NETWORK_FUNCTION(MSG_CAMERA_INFO);
    ADD_NETWORK_FUNCTION(MSG_REQUEST_TANKS);
    ADD_NETWORK_FUNCTION(MSG_SEND_LANDSCAPE);
    ADD_NETWORK_FUNCTION(MSG_SEND_TANKS);
    ADD_NETWORK_FUNCTION(MSG_SEND_SCREENSHOT);
    ADD_NETWORK_FUNCTION(MSG_DELETE_SERVER);
    ADD_NETWORK_FUNCTION(MSG_SET_NETWORK_LOSS);
    ADD_NETWORK_FUNCTION(MSG_SET_NETWORK_LATENCY);
}


void Battler::OpenLog()
{
    TheLog = new LogRTS();
    char buffer[50];
    srand(static_cast<uint>(time(static_cast<time_t*>(0)))); //-V202

    if (MODE_SERVER)
    {
        sprintf_s(buffer, 50, "server.log");
    }
    else if (MODE_CLIENT)
    {
        sprintf_s(buffer, 50, "client.log");
    }
    else
    {
        sprintf_s(buffer, 50, "log.log");
    }

    TheLog->Open(buffer);
    TheLog->SetLevel(LOG_DEBUG);
}
