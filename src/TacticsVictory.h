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
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    void HandleMenuEvent(StringHash eventType, VariantMap& eventData);
    void HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData);
    void HandleKeyDown(StringHash eventType, VariantMap& eventData);

    bool drawDebug = false;

    TacticsVictory& operator=(const TacticsVictory&)
    {};
};
