// 2021/04/02 17:53:03 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Hangar.h"


#pragma warning(push)
#pragma warning(disable:4100)
URHO3D_DEFINE_APPLICATION_MAIN(Hangar)
#pragma warning(pop)


Hangar::Hangar(Context* context) :
    Application(context)
{
    TheContext = context;
}


void Hangar::Setup()
{
    OpenLog();

    TheConfig.Load("Hangar.cfg");

    TheHangar = this;

    TheMaster.Connect(TheConfig.GetString("address master"));

    GetSubsystems();

    TuneEngineParameters();
}


void Hangar::GetSubsystems()
{
}


void Hangar::TuneEngineParameters()
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

//    TheCache->AddResourceDir(RESOURCES_DIR);
}


void Hangar::Start()
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


void Hangar::CreateGUI()
{
}


void Hangar::Stop()
{
}


void Hangar::SetLocalization()
{
}


void Hangar::RegistrationObjects()
{
}


void Hangar::SubscribeToEvents()
{
}


void Hangar::SetWindowTitleAndIcon()
{
}


void Hangar::CreateConsoleAndDebugHud()
{
}


void Hangar::OpenLog()
{
    log = new Log(TheContext);
    log->Open(GetTypeName() + ".log");
    log->SetLevel(LOG_DEBUG);
}
