// 2021/04/02 17:53:03 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Client.h"


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
    LogRAW::Create("Client.log");

    LOGWRITE("Start Client");

    TheConfig.Load("Client.conf");

    TheMaster.Connect();

    std::string address = TheMaster.GetValue(MASTER_GET_ADDRESS_UPLOADER);

    TheMaster.Destroy();

    LOGWRITE("Address uploader is %s", address.c_str());

    TheClient = this;

    GetSubsystems();

    TuneEngineParameters();
}


void Client::GetSubsystems()
{
    TheCache = GetSubsystem<ResourceCache>();
}


void Client::TuneEngineParameters()
{
    engineParameters_[EP_WINDOW_TITLE] = GetTypeName();
    engineParameters_[EP_LOG_NAME] = GetSubsystem<FileSystem>()->
                                                        GetAppPreferencesDir("urho3d", "logs") + GetTypeName() + ".log";
    engineParameters_[EP_FULL_SCREEN] = false;
    engineParameters_[EP_TEXTURE_QUALITY] = 32; //-V112
//    engineParameters_[EP_WINDOW_WIDTH] = TheSet->GetInt(TV_SCREEN_WIDTH);
//    engineParameters_[EP_WINDOW_HEIGHT] = TheSet->GetInt(TV_SCREEN_HEIGHT);
    engineParameters_[EP_HEADLESS] = false;

    if (!engineParameters_.Contains(EP_RESOURCE_PREFIX_PATHS))
#ifdef DEBUG
        engineParameters_[EP_RESOURCE_PREFIX_PATHS] = ";../../../../../../out/debug";
#else
        engineParameters_[EP_RESOURCE_PREFIX_PATHS] = ";../../../../../../out/release";
#endif

//    TheCache->AddResourceDir(RESOURCES_DIR);
}


void Client::Start()
{
    OpenLog();

    GetSubsystems();

    Application::Start();

    SetLocalization();

    RegistrationObjects();

    SetWindowTitleAndIcon();

    CreateConsoleAndDebugHud();

    SubscribeToEvents();

    CreateGUI();
}


void Client::CreateGUI()
{
}


void Client::Stop()
{
    LOGWRITE("Stop Client");
}


void Client::SetLocalization()
{
}


void Client::RegistrationObjects()
{
}


void Client::SubscribeToEvents()
{
}


void Client::SetWindowTitleAndIcon()
{
}


void Client::CreateConsoleAndDebugHud()
{
}


void Client::OpenLog()
{
}
