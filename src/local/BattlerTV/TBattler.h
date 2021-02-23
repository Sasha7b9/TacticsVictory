// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class TScene;


class Battler : public Application
{
    URHO3D_OBJECT(Battler, Application);

public:
    Battler(Context* context);

    virtual void Setup();
    virtual void Start();
    virtual void Stop();
    void StartServer(uint16 port = 0);
    void StopServer();
    void StartClient(const String &address = String::EMPTY, uint16 port = 0);
    void StopClient();

    TScene *scene = nullptr; //-V122

private:
    bool drawDebug = false;
    String address = String::EMPTY;
    uint16 port = 0;

    void OpenLog();
    void ParseArguments(const Vector<String> &arguments);
    void RegistrationComponets();
    void SetWindowTitleAndIcon();
    void CreateConsoleAndDebugHud();
    void CreateEditorSession();
    void SubscribeToEvents();
    void SetLocalization();
    void CreateScriptSystem();

    void HandleMenuEvent(StringHash, VariantMap&);
    void HandlePostRenderUpdate(StringHash, VariantMap&);
    void HandleKeyDown(StringHash, VariantMap&);
};
