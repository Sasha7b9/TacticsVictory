// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Battle.h"
#include "Core/Math_.h"
#include "Game/Logic/Rotator_.h"
#include "Game/Logic/SunEngine_.h"
#include "Game/Path/WaveAlgorithm_.h"
#include "Network/ServerS.h"
#include "Scene/Level_.h"
#include "Scene/SceneS.h"
#include "Scene/Objects/Units/Air/AirPlane/AirPlane_.h"
#include "Scene/Objects/Units/Ground/Tank/Tank_.h"
#include "Utils/Log_.h"
#include "Utils/Settings.h"


#ifdef WIN32
#pragma warning(push, 0)
#endif
URHO3D_DEFINE_APPLICATION_MAIN(Battle)
#ifdef WIN32
#pragma warning(pop)
#endif


/*
*  Запуск сервера:
*   ./BattleTV
*       -exit:       : когда завершать функционирование сервера
*             auto   - автоматическое завершение после отключения последнего игрока
*             manual - ручное отключение / kill -9 $(pidof BattleTV) /
*       -level:file_name.json : имя файла с уровнем
*       -players:
*  Первый вариант оцции выбиратеся по умолчаюнию
*/


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

    TheScene = new SceneS();

    TheLevel = new Level();

    TheLevel->Load("Game/Levels/level.map");

    TheScene->Create();

    float rangeX = (float)TheTerrain->HeightX();
    float rangeZ = (float)TheTerrain->WidthZ();

    for (int i = 0; i < 1000; i++)
    {
        ObjectCreator::Create<Tank>(Math::RandomUINT(rangeX), Math::RandomUINT(rangeZ));

        ObjectCreator::Create<AirPlane>(Math::RandomUINT(rangeX), Math::RandomUINT(rangeZ));
    }

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
    SunEngine::RegisterComponent();
    Rotator::RegisterComponent();
    WaveAlgorithm::RegisterComponent();

    AirPlane::RegisterComponent();
    Tank::RegisterComponent();
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
