// 2021/04/02 17:53:21 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/GUI.h"


class SceneT;


class Client : public Application
{
    URHO3D_OBJECT(Client, Application);
public:
    Client(Context* context);

    virtual void Setup();
    virtual void Start();

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

    SharedPtr<Log>      log;
    SharedPtr<GUI>      gui;
    SharedPtr<Settings> settings;
    SharedPtr<Mouse>    mouse;
    SharedPtr<MenuT>    menu;
};
