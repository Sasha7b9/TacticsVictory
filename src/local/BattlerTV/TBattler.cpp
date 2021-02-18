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
    engineParameters_[EP_HEADLESS] = false;

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
    SAFE_DELETE(TheScene);
    SAFE_DELETE(scene);
    SAFE_DELETE(TheFileSelector);
    SAFE_DELETE(TheLevel);
    SAFE_DELETE(TheMenu);
    SAFE_DELETE(TheGUI);
    TheSet->Save();
    SAFE_DELETE(TheSet);
    SAFE_DELETE(TheEditor);
    SAFE_DELETE(TheCamera);
    TheLog->Close();
    SAFE_DELETE(TheLog);
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
    TheCache->AddResourceDir("TVData");
    SetLocalization();
    TheTime = GetSubsystem<Time>();
    TheFont = TheCache->GetResource<Font>(SET::MENU::FONT::NAME);
    TheProfiler = GetSubsystem<Profiler>();
    TheEngine = GetSubsystem<Engine>();
    TheGraphics = GetSubsystem<Graphics>();

    TheScene = new TScene(TheContext);

    TheScene->scene->CreateComponent<Octree>();
    ThePhysicsWorld = TheScene->scene->CreateComponent<PhysicsWorld>();
    ThePhysicsWorld->SetGravity(Vector3::ZERO);
    TheScene->scene->CreateComponent<DebugRenderer>();

    CreateScriptSystem();

    SetWindowTitleAndIcon();
    CreateConsoleAndDebugHud();
    TheUI = GetSubsystem<UI>();
    TheInput = GetSubsystem<Input>();
    TheAudio = GetSubsystem<Audio>();
    TheRenderer = GetSubsystem<Renderer>();
    TheCamera = new TCamera();
    TheDebugRenderer = TheScene->scene->GetComponent<DebugRenderer>();
    TheUIRoot = TheUI->GetRoot();
    TheUIRoot->SetDefaultStyle(TheCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    TheGUI = new GUI();
    LOGINFO("Загружаю настройки");
    TheMenu = new MenuTV();
    TheFileSelector = new FileSelector(TheContext);
    TheFileSelector->GetWindow()->SetModal(false);
    TheFileSelector->GetWindow()->SetVisible(false);

    RegistrationComponets();

    TheLevel = new Level();

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
    UNUSED(port_);

//    if (port_)
//    {
//        port = port_;
//    }
//
//    if (port)
//    {
//        TheServer->Start(port);
//        scene = new TScene(TheContext, TScene::Mode_Server);
//        scene->Create();
//    }
//    else
//    {
//        LOGERROR("Can not start server on null port");
//    }
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
    UNUSED(arguments);
}


void Battler::RegistrationComponets()
{
    TheContext->RegisterFactory<Rotator>();
    TheContext->RegisterFactory<Movinator>();
    TheContext->RegisterFactory<ImageTV>();

    RocketLauncher::RegisterObject();

    Translator::RegisterObject();
    WaveAlgorithm::RegisterObject();
    Tank::RegisterObject();

    TScene::RegisterObject();
}


void Battler::SubscribeToEvents()
{
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(Battler, HandleKeyDown));
    SubscribeToEvent(E_MENU, URHO3D_HANDLER(Battler, HandleMenuEvent));
    SubscribeToEvent(E_POSTRENDERUPDATE, URHO3D_HANDLER(Battler, HandlePostRenderUpdate));

    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(Battler, HandleUpdate));
    SubscribeToEvent(E_POSTUPDATE, URHO3D_HANDLER(Battler, HandlePostUpdate));
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
        TheEditor = new Editor(TheContext);
    }
    TheGuiEditor->SetVisible(true);
    TheCamera->SetEnabled(true);
    TheEditor->Run();
}


void Battler::OpenLog()
{
    TheLog = new CLog();
    char buffer[50];
    srand(static_cast<uint>(time(static_cast<time_t*>(0)))); //-V202

    sprintf_s(buffer, 50, "Battler.log");

    TheLog->Open(buffer);
    TheLog->SetLevel(LOG_DEBUG);
}
