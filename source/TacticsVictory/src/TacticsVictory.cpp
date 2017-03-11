#include <stdafx.h>
#include "Core/Camera.h"
#include "GlobalFunctions.h"
#include "LogRTS.h"
#include "Editor/Editor.h"
#include "Game/Level.h"
#include "Game/Scene.h"
#include "Game/Logic/Movinator.h"
#include "Game/Logic/Rotator.h"
#include "Game/Objects/Ammo/Rocket/Rocket.h"
#include "Game/Path/TilePath.h"
#include "GUI/GUI.h"
#include "GUI/Cursor.h"
#include "GUI/GuiEditor/GuiEditor.h"
#include "GUI/GuiGame/GuiGame.h"
#include "GUI/Menu/MenuRTS.h"
#include "GUI/Windows/Console.h"
#include "Network/Client.h"
#include "Network/Server.h"
#include "Network/NetworkMessages.h"
#include "Network/ClientFunctions.h"
#include "Network/ServerFunctions.h"
#include "TacticsVictory.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma warning(push)
#pragma warning(disable:4100)
URHO3D_DEFINE_APPLICATION_MAIN(TacticsVictory)
#pragma warning(pop)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TacticsVictory::TacticsVictory(Context* context) :
    Application(context)
{
    gContext = context;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::Setup()
{
    FillNetworkFunctions();

    gTacticsVictory = this;
    gSet = new Settings();
    gCache = GetSubsystem<ResourceCache>();
    gFileSystem = GetSubsystem<FileSystem>();
    gSet->Load();

    engineParameters_["WindowTitle"] = GetTypeName();
    engineParameters_["LogName"] = GetSubsystem<FileSystem>()->GetAppPreferencesDir("urho3d", "logs") + GetTypeName() + ".log";
    engineParameters_["FullScreen"] = false;
    
    engineParameters_["TextureQuality"] = 32; //-V112
    engineParameters_["WindowWidth"] = gSet->GetInt(TV_SCREEN_WIDTH);
    engineParameters_["WindowHeight"] = gSet->GetInt(TV_SCREEN_HEIGHT);

#ifdef CLIENT
    engineParameters_["Headless"] = false;
#else
    engineParameters_["Headless"] = true;
#endif
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::Stop()
{
    engine_->DumpResources(true);
    //engine_->DumpProfiler();
    TilePath::RemoveAll();
    Rocket::DeleteAll();
    SAFE_DELETE(gScene); //-V809
    SAFE_DELETE(scene); //-V809
    SAFE_DELETE(gFileSelector); //-V809
    SAFE_DELETE(gLevel); //-V809
    SAFE_DELETE(gMenu); //-V809
    SAFE_DELETE(gGUI); //-V809
    //File file(gContext, "ui.xml", FILE_WRITE);
    //URHO3D_LOGINFO("Now save ui");
    //gUIRoot->SaveXML(file);
    gSet->Save();
    SAFE_DELETE(gClient); //-V809
    SAFE_DELETE(gServer); //-V809
    SAFE_DELETE(gSet); //-V809
    SAFE_DELETE(gEditor); //-V809
    SAFE_DELETE(gCamera);     //-V809
    gLog->Close();
    SAFE_DELETE(gLog); //-V809
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::Start()
{
    gProfiler = GetSubsystem<Profiler>();
    PROFILER_FUNC_ENTER
    Application::Start();

    gTime = GetSubsystem<Time>();

    OpenLog();

    RegistrationFactories();

    gCache->AddResourceDir(gFileSystem->GetProgramDir() + RESOURCES_DIR);
    gFont = gCache->GetResource<Font>(SET::MENU::FONT::NAME);

    gProfiler = GetSubsystem<Profiler>();
    gLocalization = GetSubsystem<Localization>();
    gLocalization->LoadJSONFile("Strings.json");
    gLocalization->SetLanguage("ru");
    gUI = GetSubsystem<UI>();
    gEngine = GetSubsystem<Engine>();
    gInput = GetSubsystem<Input>();
#ifdef CLIENT
    gRenderer = GetSubsystem<Renderer>();
#endif
    gGraphics = GetSubsystem<Graphics>();

    XMLFile *style = gCache->GetResource<XMLFile>("UI/MainStyle.xml");
    gUIRoot = gUI->GetRoot();
    gUIRoot->SetDefaultStyle(style);

    SetWindowTitleAndIcon();
    CreateConsoleAndDebugHud();

    CreateComponents();

    gCamera = new CameraRTS();

    gLog->SetLevel(LOG_ERROR);
#ifdef CLIENT
    gGUI->Create();

    gFileSelector = new FileSelector(gContext);
    gFileSelector->GetWindow()->SetModal(false);
    gFileSelector->GetWindow()->SetVisible(false);
#endif
    gLog->SetLevel(LOG_INFO);

    SubscribeToEvents();

    gContext->RegisterSubsystem(new Script(gContext));
    gScript = GetSubsystem<Script>();
    gScript->Execute("Print(\"Hello World!\");");

    Vector<String> arguments = GetArguments();

    gClient = new Client();
    gServer = new Server();

    ParseArguments(arguments);

    PROFILER_FUNC_LEAVE;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::ParseArguments(Vector<String> &arguments)
{
    String address;
    uint16 port = 0;
    GetAddressPort(arguments, address, port);

#ifdef SERVER
    if(port == 0)
    {
        gEngine->Exit();
    }

    StartServer(port);
#else
    
#endif
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::CreateComponents()
{
    gScene = new Scene(gContext);
    // Create the Octree component to the scene so that drawable objects can be rendered. Use default volume (-1000, -1000, -1000) to (1000, 1000, 1000)
    gScene->CreateComponent<Octree>();

    gPhysicsWorld = gScene->CreateComponent<PhysicsWorld>();
    gPhysicsWorld->SetGravity(Vector3::ZERO);

    gScene->CreateComponent<DebugRenderer>();
    gDebugRenderer = gScene->GetComponent<DebugRenderer>();

    gGUI = new GUI();

    GUI::RegistrationObjects();

    gLog->SetLevel(LOG_ERROR);
#ifdef CLIENT
    gMenu = new MenuRTS();
#endif
    gLog->SetLevel(LOG_ERROR);

    gLevel = new Level();

#ifdef CLIENT
    gAudio = GetSubsystem<Audio>();
#endif

    SceneRTS::RegisterObject();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::RegistrationFactories()
{
    gContext->RegisterFactory<Rotator>();
    gContext->RegisterFactory<Movinator>();
    gContext->RegisterFactory<ImageRTS>();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::SubscribeToEvents()
{
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(TacticsVictory, HandleUpdate));
    SubscribeToEvent(E_POSTRENDERUPDATE, URHO3D_HANDLER(TacticsVictory, HandlePostRenderUpdate));
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(TacticsVictory, HandleKeyDown));
    SubscribeToEvent(E_MENU, URHO3D_HANDLER(TacticsVictory, HandleMenuEvent));
    SubscribeToEvent(E_POSTUPDATE, URHO3D_HANDLER(TacticsVictory, HandlePostUpdate));

    SubscribeToEvent(E_CONNECTFAILED, URHO3D_HANDLER(TacticsVictory, HandleConnecFailed));
    SubscribeToEvent(E_CLIENTCONNECTED, URHO3D_HANDLER(TacticsVictory, HandleClientConnected));
    SubscribeToEvent(E_CLIENTDISCONNECTED, URHO3D_HANDLER(TacticsVictory, HandleClientDisconnected));

    SubscribeToEvent(E_NETWORKMESSAGE, URHO3D_HANDLER(TacticsVictory, HandleNetworkMessage));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::SetWindowTitleAndIcon()
{
#ifdef CLIENT
    Image* icon = gCache->GetResource<Image>("Textures/TacticsVictoryIcon.png");
    gGraphics->SetWindowIcon(icon);
    gGraphics->SetWindowTitle(L"Тактика победы");
#endif
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::CreateConsoleAndDebugHud()
{
#ifdef CLIENT
    XMLFile* xmlFile = gCache->GetResource<XMLFile>("UI/ConsoleStyle.xml");

    gEngineConsole = engine_->CreateConsole();
    gEngineConsole->SetDefaultStyle(xmlFile);
    gEngineConsole->GetBackground()->SetOpacity(0.8f);

    gDebugHud = engine_->CreateDebugHud();
    gDebugHud->SetDefaultStyle(xmlFile);
#endif
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool TacticsVictory::StartServer(uint16 port)
{
    URHO3D_LOGINFO("Now start server");
    if(gServer->Start(port))
    {
        gMenu->Hide();
        scene = new SceneRTS(gContext, SceneRTS::Mode_Server);
        scene->Create();
        gCamera->SetEnabled(true);
        return true;
    }
    URHO3D_LOGINFO("Can not start server");
    ErrorExit();
    return false;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::CreateEditorSession()
{
    if(!gEditor)
    {
        gEditor = new Editor(gContext);
    }
    gGuiEditor->SetVisible(true);
    gCamera->SetEnabled(true);
    gEditor->Run();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::FillNetworkFunctions()
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

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::OpenLog()
{
    gLog = new LogRTS();
#ifdef SERVER
    char buffer[50];
    srand((uint)time(0));
    rand();
    sprintf_s(buffer, 50, "server%d.log", rand());
    gLog->Open(buffer);
#else
    gLog->Open("client.log");
#endif
    gLog->SetLevel(LOG_DEBUG);
}
