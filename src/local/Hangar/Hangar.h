// 2021/04/02 17:53:21 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/GUI.h"
#include "GUI/Menu/Menu.h"
#include "Input/Mouse_.h"
#include "Scene/SceneC.h"


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
    void ParseArguments();


    void HandlerMenuEvent(StringHash, VariantMap &);
    void HandlerPostRenderUpdate(StringHash, VariantMap &);
    void HandlerKeyDown(StringHash, VariantMap &);

    SharedPtr<Log>    log;
    SharedPtr<SceneC> scene;
    SharedPtr<GUI>    gui;
    SharedPtr<Mouse>  mouse;
    SharedPtr<Menus>  menu;
};
