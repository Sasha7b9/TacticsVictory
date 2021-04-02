// 2021/04/02 17:53:21 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class SceneT;


class Client : public Application
{
    URHO3D_OBJECT(Client, Application);
public:
    Client(Context* context);

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
    void GetSubsystems();
    void TuneEngineParameters();
    void CreateGUI();

    void HandleMenuEvent(StringHash, VariantMap&);
    void HandlePostRenderUpdate(StringHash, VariantMap&);
    void HandleKeyDown(StringHash, VariantMap&);
};
