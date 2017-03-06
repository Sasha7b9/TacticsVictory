﻿#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SceneRTS;


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
