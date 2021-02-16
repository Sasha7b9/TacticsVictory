// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


#pragma warning(push)
#pragma warning(disable:4100)
URHO3D_DEFINE_APPLICATION_MAIN(Battle)
#pragma warning(pop)


Battle::Battle(Context* context) :
    Application(context)
{
    TheContext = context;
}


void Battle::Setup()
{
    TheBattle = this;
    TheSet = new Settings();
    TheCache = GetSubsystem<ResourceCache>();
    TheFileSystem = GetSubsystem<FileSystem>();
    OpenLog();
    TheSet->Load();

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


void Battle::Start()
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
    TheScene = new SceneTV(TheContext);
    TheScene->scene->CreateComponent<Octree>();
    ThePhysicsWorld = TheScene->scene->CreateComponent<PhysicsWorld>();
    ThePhysicsWorld->SetGravity(Vector3::ZERO);
    TheScene->scene->CreateComponent<DebugRenderer>();
    scene = new SceneTV();

    CreateScriptSystem();

    RegistrationComponets();

    scene->Create();

    LOGINFO("Загружаю настройки");
    
    TheLevel = new Level();

    SubscribeToEvents();

    PROFILER_FUNC_LEAVE;
}


void Battle::Stop()
{
    engine_->DumpResources(true);
    //engine_->DumpProfiler();
    Rocket::DeleteAll();
    SAFE_DELETE(TheScene); //-V809
    SAFE_DELETE(scene); //-V809
    SAFE_DELETE(TheLevel); //-V809
    TheSet->Save();
    SAFE_DELETE(TheSet); //-V809
    TheLog->Close();
    SAFE_DELETE(TheLog); //-V809
}


void Battle::SetLocalization()
{
    TheLocalization = GetSubsystem<Localization>();
    TheLocalization->LoadJSONFile("TVData/Strings.json");
    TheLocalization->SetLanguage("ru");
}


static void MessageCallback(const asSMessageInfo *msg, void *)
{
    const char *type = "AS ERROR ";
    if (msg->type == asMSGTYPE_WARNING)
        type = "AS WARN ";
    else if (msg->type == asMSGTYPE_INFORMATION)
        type = "AS INFO ";

    LOGINFOF("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message); //-V111
}


void Battle::CreateScriptSystem()
{
    TheContext->RegisterSubsystem(new Script(TheContext));
    TheScript = GetSubsystem<Script>();
    TheScript->GetScriptEngine()->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);
}


void Battle::RegistrationComponets()
{
    TheContext->RegisterFactory<Rotator>();
    TheContext->RegisterFactory<Movinator>();

    SceneTV::RegisterObject();

    RocketLauncher::RegisterInAS();
    Translator::RegisterInAS();
    Tank::RegisterInAS();
}


void Battle::SubscribeToEvents()
{
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(Battle, HandleUpdate));
    SubscribeToEvent(E_POSTUPDATE, URHO3D_HANDLER(Battle, HandlePostUpdate));
}


void Battle::OpenLog()
{
    TheLog = new LogTV();
    char buffer[50];
    srand(static_cast<uint>(time(static_cast<time_t*>(0)))); //-V202

    sprintf_s(buffer, 50, "TV.log");

    TheLog->Open(buffer);
    TheLog->SetLevel(LOG_DEBUG);
}
