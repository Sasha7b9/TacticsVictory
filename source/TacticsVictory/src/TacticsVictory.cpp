// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
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
    ParseArguments(GetArguments());

    gTacticsVictory = this;
    gSet = new Settings();
    gCache = GetSubsystem<ResourceCache>();
    gFileSystem = GetSubsystem<FileSystem>();
    gSet->Load();

    engineParameters_[EP_WINDOW_TITLE] = GetTypeName();
    engineParameters_[EP_LOG_NAME] = GetSubsystem<FileSystem>()->GetAppPreferencesDir("urho3d", "logs") + GetTypeName() + ".log";
    engineParameters_[EP_FULL_SCREEN] = false;
    engineParameters_[EP_TEXTURE_QUALITY] = 32; //-V112
    engineParameters_[EP_WINDOW_WIDTH] = gSet->GetInt(TV_SCREEN_WIDTH);
    engineParameters_[EP_WINDOW_HEIGHT] = gSet->GetInt(TV_SCREEN_HEIGHT);
    engineParameters_[EP_HEADLESS] = MODE_SERVER;
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
void MessageCallback(const asSMessageInfo *msg, void *)
{
    const char *type = "AS ERROR ";
    if(msg->type == asMSGTYPE_WARNING)
        type = "AS WARN ";
    else if(msg->type == asMSGTYPE_INFORMATION)
        type = "AS INFO ";

    LOG_INFOF("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::Start()
{
    gProfiler = GetSubsystem<Profiler>();
    PROFILER_FUNC_ENTER
    Application::Start();
    FillNetworkFunctions();
    gTime = GetSubsystem<Time>();
    OpenLog();
    RegistrationComponets();
    gCache->AddResourceDir(gFileSystem->GetProgramDir() + RESOURCES_DIR);
    gFont = gCache->GetResource<Font>(SET::MENU::FONT::NAME);
    gProfiler = GetSubsystem<Profiler>();
    gLocalization = GetSubsystem<Localization>();
    gLocalization->LoadJSONFile("Strings.json");
    gLocalization->SetLanguage("ru");
    gEngine = GetSubsystem<Engine>();
    gGraphics = GetSubsystem<Graphics>();

    if (!MODE_SERVER)
    {
        gUI = GetSubsystem<UI>();
        gInput = GetSubsystem<Input>();
        gRenderer = GetSubsystem<Renderer>();
        SetWindowTitleAndIcon();
        CreateConsoleAndDebugHud();
        gDebugRenderer = gScene->GetComponent<DebugRenderer>();
    }
    

    XMLFile *style = gCache->GetResource<XMLFile>("UI/MainStyle.xml");
    gUIRoot = gUI->GetRoot();
    gUIRoot->SetDefaultStyle(style);
    gScene = new Scene(gContext);
    // Create the Octree component to the scene so that drawable objects can be rendered. Use default volume (-1000, -1000, -1000) to (1000, 1000, 1000)
    gScene->CreateComponent<Octree>();
    gPhysicsWorld = gScene->CreateComponent<PhysicsWorld>();
    gPhysicsWorld->SetGravity(Vector3::ZERO);
    gScene->CreateComponent<DebugRenderer>();
    gGUI = new GUI();
    GUI::RegistrationObjects();
    gLog->SetLevel(LOG_ERROR);

    if (MODE_CLIENT)
    {
        gAudio = GetSubsystem<Audio>();
        gMenu = new MenuRTS();
        gGUI->Create();
        gFileSelector = new FileSelector(gContext);
        gFileSelector->GetWindow()->SetModal(false);
        gFileSelector->GetWindow()->SetVisible(false);
    }

    gLog->SetLevel(LOG_ERROR);
    gLevel = new Level();
    SceneRTS::RegisterObject();
    gLog->SetLevel(LOG_ERROR);
    gLog->SetLevel(LOG_INFO);
    gContext->RegisterSubsystem(new Script(gContext));
    gScript = GetSubsystem<Script>();
    gScript->GetScriptEngine()->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);
    gClient = new Client();
    gServer = new Server();

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

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool TacticsVictory::StartServer(uint16 port_)
{
    URHO3D_LOGINFO("Now start server");
    if (gServer->Start(port_))
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
void TacticsVictory::StartClient(String &address_, uint16 port_)
{
    SAFE_DELETE(gCamera);
    gCamera = new CameraRTS();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::ParseArguments(const Vector<String> &arguments)
{
    /*
        1. нет аргументов - просто запуск
        2. аргументы -port:XX - запуск сервера на порту XX
        3. аргументы -address:XX.XX.XX.XX -port:XX - запуск оболочки и коннект к серверу на XX.XX.XX.XX:XX
    */

    if (GetAddressPort(arguments, address, port))
    {
        gMode = address.Empty() ? ModeApp_Server : ModeApp_Client;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::RegistrationComponets()
{
    gContext->RegisterFactory<Rotator>();
    gContext->RegisterFactory<Movinator>();
    gContext->RegisterFactory<ImageRTS>();

    RocketLauncher::RegisterInAS();
    Translator::RegisterInAS();
    WaveAlgorithm::RegisterInAS();
    Tank::RegisterInAS();
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
    if (MODE_CLIENT)
    {
        Image* icon = gCache->GetResource<Image>("Textures/TacticsVictoryIcon.png");
        gGraphics->SetWindowIcon(icon);
        gGraphics->SetWindowTitle(L"Тактика победы");
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::CreateConsoleAndDebugHud()
{
    if (MODE_CLIENT)
    {
        XMLFile* xmlFile = gCache->GetResource<XMLFile>("UI/ConsoleStyle.xml");

        gEngineConsole = engine_->CreateConsole();
        gEngineConsole->SetDefaultStyle(xmlFile);
        gEngineConsole->GetBackground()->SetOpacity(0.8f);

        gDebugHud = engine_->CreateDebugHud();
        gDebugHud->SetDefaultStyle(xmlFile);
    }
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

    if (MODE_SERVER)
    {
        char buffer[50];
        srand(static_cast<uint>(time(static_cast<time_t*>(0))));
        rand();
        sprintf_s(buffer, 50, "server%d.log", rand());
        gLog->Open(buffer);
    }

    if (MODE_CLIENT)
    {
        gLog->Open("client.log");
    }

    gLog->SetLevel(LOG_DEBUG);
}
