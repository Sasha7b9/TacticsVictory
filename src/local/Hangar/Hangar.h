// 2021/04/02 17:53:21 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class Hangar : public Application
{
    URHO3D_OBJECT(Hangar, Application);
public:
    Hangar(Context* context);

    virtual void Setup();
    virtual void Start();
    virtual void Stop();

    bool drawDebug = false;

private:

    void OpenLog();
    void RegistrationObjects();
    void SetWindowTitleAndIcon();
    void CreateConsoleAndDebugHud();
    void SubscribeToEvents();
    void SetLocalization();
    void GetSubsystems();
    void TuneEngineParameters();
    void CreateGUI();
};
