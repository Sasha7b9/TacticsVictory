// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class SceneTV;


class Battle : public Application
{
    URHO3D_OBJECT(Battle, Application);

public:
    Battle(Context* context);

    virtual void Setup();
    virtual void Start();
    virtual void Stop();

    SceneTV *scene = nullptr; //-V122

private:
    bool drawDebug = false;

    void OpenLog();
    void RegistrationComponets();
    void SubscribeToEvents();
    void SetLocalization();
    void CreateScriptSystem();

    void HandleUpdate(StringHash, VariantMap&);
    void HandlePostUpdate(StringHash, VariantMap&);
};
