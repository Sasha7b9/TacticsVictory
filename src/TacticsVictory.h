#pragma once


class lScene;


class TacticsVictory : public Application
{
    URHO3D_OBJECT(TacticsVictory, Application);

public:
    TacticsVictory(Context* context);

    virtual void Setup();
    virtual void Start();
    virtual void Stop();

private:
    void InitWindow();
    void CreateComponents();
    void RegistrationFactories();
    void InitLocalizationSystem();
    void SetWindowTitleAndIcon();
    void CreateConsoleAndDebugHud();
    void CreateNewGame();
    void CreateEditorSession();
    void SaveSettings();

    void SubscribeToEvents();
    void HandleUpdate(StringHash, VariantMap&);
    void HandlePostUpdate(StringHash, VariantMap&);
    void HandleMenuEvent(StringHash, VariantMap&);
    void HandlePostRenderUpdate(StringHash, VariantMap&);
    void HandleKeyDown(StringHash, VariantMap&);

    bool drawDebug = false;
    lScene *scene = nullptr;

    TacticsVictory& operator=(const TacticsVictory&)
    {};
};
