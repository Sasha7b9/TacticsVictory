// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Battle.h"
#include "Game/Logic/Rotator_.h"
#include "Game/Logic/SunEngine_.h"
#include "Network/ServerS.h"
#include "Scene/Level_.h"
#include "Scene/Scene_.h"
#include "Utils/Log_.h"
#include "Utils/Settings.h"


#ifdef WIN32
#pragma warning(push, 0)
#endif
URHO3D_DEFINE_APPLICATION_MAIN(Battle)
#ifdef WIN32
#pragma warning(pop)
#endif


Battle::Battle(Context* context) :
    Application(context)
{
    TheContext = context;
}


void Battle::Setup()
{
    TheBattle = this;

    GetSubsystems();

    OpenLog();

    TheSet = new Settings();

    TheSet->Load();

    TuneEngineParameters();  
}


void Battle::GetSubsystems()
{
    TheCache = GetSubsystem<ResourceCache>();
    TheFileSystem = GetSubsystem<FileSystem>();
    TheTime = GetSubsystem<Time>();
    TheProfiler = GetSubsystem<Profiler>();
    TheEngine = GetSubsystem<Engine>();
    TheLocalization = GetSubsystem<Localization>();
    TheNetwork = GetSubsystem<Network>();

    CreateScriptSystem();
}


void Battle::TuneEngineParameters()
{
    engineParameters_[EP_LOG_NAME] = GetSubsystem<FileSystem>()->GetAppPreferencesDir("urho3d", "logs") + GetTypeName() + ".log";
    engineParameters_[EP_HEADLESS] = true;

    if (!engineParameters_.Contains(EP_RESOURCE_PREFIX_PATHS))
#ifdef DEBUG
        engineParameters_[EP_RESOURCE_PREFIX_PATHS] = ";../../../../../../out/debug";
#else
        engineParameters_[EP_RESOURCE_PREFIX_PATHS] = ";../../../../../../out/release";
#endif

    TheCache->AddResourceDir(RESOURCES_DIR);
}


void Battle::Start()
{
    PROFILER_FUNC_ENTER();

    GetSubsystems();

    Application::Start();

    SetLocalization();

    RegistrationComponets();

    TheScene = new SceneT();

    TheLevel = new Level();

    TheScene->Create();

    SubscribeToEvents();

    TheServer = new ServerS();

    TheServer->Start(SERVER_PORT);

    PROFILER_FUNC_LEAVE();
}


void Battle::Stop()
{
    engine_->DumpResources(true);
    engine_->DumpProfiler();

    delete TheScene;
    delete TheLevel;
    delete TheSet;
    delete TheLog;
    delete TheServer;
}


void Battle::SetLocalization()
{
    TheLocalization = GetSubsystem<Localization>();
    TheLocalization->LoadJSONFile("Strings.json");
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
    SunEngine::RegisterObject();
    Rotator::RegisterObject();

    SceneT::RegisterObject();
}


void Battle::SubscribeToEvents()
{
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(Battle, HandleUpdate));
    SubscribeToEvent(E_POSTUPDATE, URHO3D_HANDLER(Battle, HandlePostUpdate));
}


void Battle::OpenLog()
{
    TheLog = new LogT();
    TheLog->Open(GetTypeName() + ".log");
    TheLog->SetLevel(LOG_DEBUG);
}
