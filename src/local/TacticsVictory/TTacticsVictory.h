// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class TScene;


class TacticsVictory : public Application
{
    URHO3D_OBJECT(TacticsVictory, Application);

public:
    TacticsVictory(Context* context);

    virtual void Setup();
    virtual void Start();
    virtual void Stop();

private:
    bool drawDebug = false;

    void OpenLog();
    void RegistrationComponets();
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
};
