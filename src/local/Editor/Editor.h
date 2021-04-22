// 2021/04/02 17:53:21 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/GUI.h"
#include "Input/Mouse_v.h"
#include "GUI/Menu/Menu.h"


class Editor : public Application
{
    URHO3D_OBJECT(Editor, Application);
public:
    Editor(Context* context);

    virtual void Setup()  override;
    virtual void Start() override;
    virtual void Stop() override;

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

    SharedPtr<Log>   log;
    SharedPtr<GUI>   gui;
    SharedPtr<Mouse> mouse;
    SharedPtr<Menus> menu;
};
