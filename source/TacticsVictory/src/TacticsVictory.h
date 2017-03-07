#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SceneRTS;

enum TypeApplication
{
    Type_None,          // Это если запускаем без параметров
    Type_Server,        // Это для запуска в режиме сервера
    Type_Client         // Это для запуска в режиме клиента
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TacticsVictory : public Application
{
    URHO3D_OBJECT(TacticsVictory, Application);

public:
    TacticsVictory(Context* context);

    virtual void Setup();
    virtual void Start();
    virtual void Stop();
    void StartServer();
    void StartClient();

    SceneRTS *scene = nullptr;

private:
    bool drawDebug = false;
    TypeApplication type = Type_None;

    void ParseArguments(Vector<String> &arguments);
    void CreateComponents();
    void RegistrationFactories();
    void SetWindowTitleAndIcon();
    void CreateConsoleAndDebugHud();
    void CreateEditorSession();
    void SubscribeToEvents();

    void HandleUpdate(StringHash, VariantMap&);
    void HandlePostUpdate(StringHash, VariantMap&);
    void HandleMenuEvent(StringHash, VariantMap&);
    void HandlePostRenderUpdate(StringHash, VariantMap&);
    void HandleKeyDown(StringHash, VariantMap&);

    void HandleServerConnected(StringHash, VariantMap&);    // Случается у клиента, когда он подключается к серверу
    void HandleServerDisconnected(StringHash, VariantMap&); // Случается у клиента, когда он отключается от сервера
    void HandleConnecFailed(StringHash, VariantMap&);
    void HandleClientConnected(StringHash, VariantMap&);    // Это на сервере, когда к нему подключается новый клиент
    void HandleClientDisconnected(StringHash, VariantMap&); // На сервере, когда отключается клиент
    void HandleNetworkMessage(StringHash, VariantMap&);

    DEFAULT_MEMBERS(TacticsVictory);
};
