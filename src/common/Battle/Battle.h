// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Network/ServerS.h"
#include "Scene/SceneS.h"


class Battle : public Application
{
    URHO3D_OBJECT(Battle, Application);

public:
    Battle(Context* context);

    virtual void Setup();
    virtual void Start();
    virtual void Stop();

private:
    bool drawDebug = false;

    void OpenLog();
    void RegistrationComponets();
    void SubscribeToEvents();
    void SetLocalization();
    void CreateScriptSystem();
    void GetSubsystems();
    void TuneEngineParameters();

    void HandlerUpdate(StringHash, VariantMap&);
    void HandlerPostUpdate(StringHash, VariantMap&);

    SharedPtr<SceneS>   scene;
    SharedPtr<Log>      log;
    SharedPtr<ServerS>  server;
};
