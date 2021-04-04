// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class SceneT;


class Battler : public Application
{
    URHO3D_OBJECT(Battler, Application);
public:
    Battler(Context* context);

    virtual void Setup();
    virtual void Start();
    virtual void Stop();

    bool drawDebug = false;

private:

    void OpenLog();
    void RegistrationObjects();
    void SetWindowTitleAndIcon();
    void CreateConsoleAndDebugHud();
    void CreateEditorSession();
    void SubscribeToEvents();
    void SetLocalization();
    void CreateScriptSystem();
    void GetSubsystems();
    void TuneEngineParameters();
    void CreateGUI();

    void HandleMenuEvent(StringHash, VariantMap&);
    void HandlePostRenderUpdate(StringHash, VariantMap&);
    void HandleKeyDown(StringHash, VariantMap&);

    SharedPtr<Log>      log;
    SharedPtr<SceneC>   scene;
    SharedPtr<ServerC>  server;
    SharedPtr<Mouse>    mouse;
    SharedPtr<MenuT>    menu;
    SharedPtr<GUI>      gui;
    SharedPtr<Editor>   editor;
};
