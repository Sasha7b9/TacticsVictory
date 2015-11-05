#pragma once


class TacticsVictory : public Urho3D::Application
{
    OBJECT(TacticsVictory);

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
    void HandleMenuEvent(StringHash, VariantMap&);
    void HandlePostRenderUpdate(StringHash, VariantMap&);
    void HandleKeyDown(StringHash, VariantMap&);

    bool drawDebug = false;
    Scene *scene = nullptr;

    TacticsVictory& operator=(const TacticsVictory&)
    {};
};
