// 2021/04/02 17:53:21 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/GUI.h"


class SceneT;


class Client : public Application
{
    URHO3D_OBJECT(Client, Application);
public:
    Client(Context* context);

    virtual void Setup()  override;
    virtual void Start() override;
    virtual void Stop() override;

    bool drawDebug = false;

    void SetWindowTitleAndIcon();

private:

    void OpenLog();
    void RegistrationObjects();
    void CreateConsoleAndDebugHud();
    void SubscribeToEvents();
    void SetLocalization();
    void GetSubsystems();
    void TuneEngineParameters();
    void CreateGUI();
    void ParseArguments();


    void HandlePostRenderUpdate(StringHash, VariantMap &);

    SharedPtr<Log>   log;
    SharedPtr<GUI>   gui;
    SharedPtr<Mouse> mouse;
    SharedPtr<Menus> menu;
};
