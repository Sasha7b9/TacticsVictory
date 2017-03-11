#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SceneRTS;
class VectorBufferRTS;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TacticsVictory : public Application
{
    URHO3D_OBJECT(TacticsVictory, Application);

public:
    TacticsVictory(Context* context);

    virtual void Setup();
    virtual void Start();
    virtual void Stop();
    bool StartServer(uint16 port);

    SceneRTS *scene = nullptr; //-V122

private:
    bool drawDebug = false;
    typedef void(*networkFunc)(Connection*, MemoryBuffer&, VectorBufferRTS&);
    HashMap<int, networkFunc> networkFunctions;                  // Здесь функции-обработчики сетевых сообщений

    void OpenLog();
    void ParseArguments(Vector<String> &arguments);
    void CreateComponents();
    void RegistrationFactories();
    void SetWindowTitleAndIcon();
    void CreateConsoleAndDebugHud();
    void CreateEditorSession();
    void SubscribeToEvents();
    void FillNetworkFunctions();

    void HandleUpdate(StringHash, VariantMap&);
    void HandlePostUpdate(StringHash, VariantMap&);
    void HandleMenuEvent(StringHash, VariantMap&);
    void HandlePostRenderUpdate(StringHash, VariantMap&);
    void HandleKeyDown(StringHash, VariantMap&);

    void HandleConnecFailed(StringHash, VariantMap&);
    void HandleClientConnected(StringHash, VariantMap&);    // Это на сервере, когда к нему подключается новый клиент
    void HandleClientDisconnected(StringHash, VariantMap&); // На сервере, когда отключается клиент
    void HandleNetworkMessage(StringHash, VariantMap&);

    DEFAULT_MEMBERS(TacticsVictory);
};
