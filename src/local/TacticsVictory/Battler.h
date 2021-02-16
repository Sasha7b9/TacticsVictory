// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class SceneRTS;
class VectorBufferRTS;


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

    SceneRTS *scene = nullptr; //-V122

private:
    bool drawDebug = false;
    typedef void(*networkFunc)(Connection*, MemoryBuffer&, VectorBufferRTS&);
    HashMap<int, networkFunc> networkFunctions;                  // Здесь функции-обработчики сетевых сообщений
    String address = String::EMPTY;
    uint16 port = 0;

    void OpenLog();
    void ParseArguments(const Vector<String> &arguments);
    void RegistrationComponets();
    void SetWindowTitleAndIcon();
    void CreateConsoleAndDebugHud();
    void CreateEditorSession();
    void SubscribeToEvents();
    void FillNetworkFunctions();
    void SetLocalization();
    void CreateScriptSystem();

    void HandleUpdate(StringHash, VariantMap&);
    void HandlePostUpdate(StringHash, VariantMap&);
    void HandleMenuEvent(StringHash, VariantMap&);
    void HandlePostRenderUpdate(StringHash, VariantMap&);
    void HandleKeyDown(StringHash, VariantMap&);
};
