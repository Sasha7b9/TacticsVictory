#include <stdafx.h>


#include "GUI/GUI.h"
#include "Core/Camera.h"
#include "Editor/Editor.h"
#include "Game/Objects/Scene.h"
#include "Game/Logic/Rotator.h"
#include "Game/Logic/Movinator.h"
#include "GUI/MenuGame/MenuGame.h"
#include "GUI/MenuEditor/MenuEditor.h"
#include "TacticsVictory.h"


#pragma warning(push)
#pragma warning(disable:4100)
DEFINE_APPLICATION_MAIN(TacticsVictory)
#pragma warning(pop)



TacticsVictory::TacticsVictory(Context* context) :
    Application(context)
{
    gContext = context;
}

void TacticsVictory::Setup()
{
    gSet = new vSettings();
    gFileSystem = GetSubsystem<FileSystem>();
    gSet->Load();

    engineParameters_["WindowTitle"] = GetTypeName();
    engineParameters_["LogName"] = GetSubsystem<FileSystem>()->GetAppPreferencesDir("urho3d", "logs") + GetTypeName() + ".log";
    engineParameters_["FullScreen"] = false;
    engineParameters_["Headless"] = false;
    engineParameters_["TextureQuality"] = 32;
    engineParameters_["WindowWidth"] = gSet->GetInt(TV_SCREEN_WIDTH);
    engineParameters_["WindowHeight"] = gSet->GetInt(TV_SCREEN_HEIGHT);
}

void TacticsVictory::Stop()
{
    SAFE_DELETE(gGUI);
    SAFE_DELETE(gTime);
    File file(gContext, "ui.xml", Urho3D::FILE_WRITE);
    gUIRoot->SaveXML(file);
    gSet->Save();
    SAFE_DELETE(gSet);
    engine_->DumpResources(true);
    SAFE_DELETE(gEditor);
    SAFE_DELETE(gScene);
    SAFE_DELETE(gCamera);
}

void TacticsVictory::CreateComponents()
{
    gLocalization = GetSubsystem<Localization>();
    gUI = GetSubsystem<UI>();
    gCache = GetSubsystem<ResourceCache>();

    gEngine = GetSubsystem<Engine>();
    gInput = GetSubsystem<Input>();
    gRenderer = GetSubsystem<Renderer>();
    gGraphics = GetSubsystem<Graphics>();

    gScene = new Scene(gContext);
    // Create the Octree component to the scene so that drawable objects can be rendered. Use default volume (-1000, -1000, -1000) to (1000, 1000, 1000)
    gScene->CreateComponent<Octree>();

    gPhysicsWorld = gScene->CreateComponent<PhysicsWorld>();

    gUIRoot = gUI->GetRoot();

    gScene->CreateComponent<DebugRenderer>();
    gDebugRenderer = gScene->GetComponent<DebugRenderer>();

    gTime = new Time(gContext);

    gGUI = new vGUI();
}

void TacticsVictory::RegistrationFactories()
{
    gContext->RegisterFactory<vRotator>();
    gContext->RegisterFactory<vMovinator>();
}

void TacticsVictory::Start()
{
    Application::Start();

    RegistrationFactories();

    CreateComponents();

    gCache->AddResourceDir(gFileSystem->GetProgramDir() + "../TVData");
    gFont = gCache->GetResource<Font>(SET::MENU::FONT::NAME);
    //gCache->AddResourceDir(gFileSystem->GetProgramDir() + "TVData");


    SetWindowTitleAndIcon();
    CreateConsoleAndDebugHud();

    XMLFile *style = gCache->GetResource<XMLFile>("UI/MainStyle.xml");
    gUIRoot->SetDefaultStyle(style);
    
    InitLocalizationSystem();

    gCamera = new vCamera();

    gGUI->Create();

    SubscribeToEvents();
}

void TacticsVictory::InitLocalizationSystem()
{
    gLocalization->LoadJSONFile("Strings.json");
    gLocalization->SetLanguage("ru");
}

void TacticsVictory::SubscribeToEvents()
{
    SubscribeToEvent(E_UPDATE, HANDLER(TacticsVictory, HandleUpdate));
    SubscribeToEvent(E_POSTRENDERUPDATE, HANDLER(TacticsVictory, HandlePostRenderUpdate));
    SubscribeToEvent(E_KEYDOWN, HANDLER(TacticsVictory, HandleKeyDown));
    SubscribeToEvent(E_MENU, HANDLER(TacticsVictory, HandleMenuEvent));
}

void TacticsVictory::SetWindowTitleAndIcon()
{
    Image* icon = gCache->GetResource<Image>("Textures/TacticsVictoryIcon.png");
    gGraphics->SetWindowIcon(icon);
    gGraphics->SetWindowTitle(L"Тактика победы");
}

void TacticsVictory::CreateConsoleAndDebugHud()
{
    XMLFile* xmlFile = gCache->GetResource<XMLFile>("UI/ConsoleStyle.xml");

    gEngineConsole = engine_->CreateConsole();
    gEngineConsole->SetDefaultStyle(xmlFile);
    gEngineConsole->GetBackground()->SetOpacity(0.8f);

    gDebugHud = engine_->CreateDebugHud();
    gDebugHud->SetDefaultStyle(xmlFile);
}

void TacticsVictory::CreateNewGame()
{
    SharedPtr<tvScene> scene(new tvScene());
    gCamera->SetEnabled(true);
    gGUI->SetVisibleMenu(false);
    gMenuGame->SetVisible(true);
    File file(gContext, "ui.xml", Urho3D::FILE_WRITE);
    gUIRoot->SaveXML(file);
    file.Close();
}

void TacticsVictory::CreateEditorSession()
{
    if(!gEditor)
    {
        gEditor = new vEditor(gContext);
    }
    gGUI->SetVisibleMenu(false);
    gMenuEditor->SetVisible(true);
    gCamera->SetEnabled(true);
    gEditor->Run();
}
