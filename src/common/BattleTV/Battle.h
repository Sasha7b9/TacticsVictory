// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class SceneRTS;
class VectorBufferRTS;


class Battle : public Application
{
    URHO3D_OBJECT(Battle, Application);

public:
    Battle(Context* context);

    virtual void Setup();
    virtual void Start();
    virtual void Stop();

    SceneRTS *scene = nullptr; //-V122

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

    void HandleUpdate(StringHash, VariantMap&);
    void HandlePostUpdate(StringHash, VariantMap&);
    void HandleMenuEvent(StringHash, VariantMap&);
    void HandlePostRenderUpdate(StringHash, VariantMap&);
    void HandleKeyDown(StringHash, VariantMap&);
};
