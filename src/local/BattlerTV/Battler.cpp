﻿// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
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
#include "Scene/Level_.h"
#include "Scene/SceneC.h"
#include "Scene/Cameras/Camera.h"
#include "Scene/Objects/Units/Tank/Tank_.h"
#include "Utils/LogC.h"
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

    OpenLog();

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
    PROFILER_FUNC_ENTER();

    GetSubsystems();

    Application::Start();

    SetLocalization();
    TheFont = TheCache->GetResource<Font>(SET::MENU::FONT::NAME);

    RegistrationComponets();

    TheMouse = new Mouse();

    TheScene = new SceneC();

    TheLevel = new Level();

    TheScene->Create();

    ThePathIndicator = new PathIndicator();

    for (int i = 0; i < 1000; i++)
    {
        uint colZ = (uint)Random((float)TheTerrain->WidthZ());
        uint rowX = (uint)Random((float)TheTerrain->HeightX());

        TheTerrain->PutIn(TheScene->CreateComponent<Tank>(), colZ, rowX);
    }

    TheCamera = TCamera::Create();

    SetWindowTitleAndIcon();

    CreateConsoleAndDebugHud();

    TheScene->CreateComponent<DebugRenderer>();
    TheDebugRenderer = TheScene->GetComponent<DebugRenderer>();

    CreateGUI();

    LOGINFO("Загружаю настройки");
    TheMenu = new TMenu();
    TheFileSelector = new FileSelector(TheContext);
    TheFileSelector->GetWindow()->SetModal(false);
    TheFileSelector->GetWindow()->SetVisible(false);

    SubscribeToEvents();

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

    delete TheMouse;
    delete ThePathIndicator;
    delete TheScene;
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
    TCamera::RegisterObject();
    TCursor::RegisterObject();
    TImage::RegisterObject();
    SunEngine::RegisterObject();
    Rotator::RegisterObject();
    WaveAlgorithm::RegisterObject();
    SceneT::RegisterObject();
    TileSelected::RegisterObject();

    GameObject::RegisterObjects();
    UnitObject::RegisterObjects();
    Tank::RegisterObject();
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
    TheLog = new CLog();
    char buffer[50];
    srand(static_cast<uint>(time(static_cast<time_t*>(0)))); //-V202

    sprintf_s(buffer, 50, "TV.log");

    TheLog->Open(buffer);
    TheLog->SetLevel(LOG_DEBUG);
}