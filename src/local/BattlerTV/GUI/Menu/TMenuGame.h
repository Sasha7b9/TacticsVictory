// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Menu/TWindowMenu.h"


class ButtonSwitch;


class MenuGame : public WindowMenu
{
    URHO3D_OBJECT(MenuGame, WindowMenu);

public:
    MenuGame(Context *context = TheContext);

    static void RegisterObject(Context *context = TheContext);
    void Open();
    void Close();

private:
    void HandleButtonRelease(StringHash, VariantMap&);  

    SharedPtr<ButtonTV> buttonNewGame;
    SharedPtr<ButtonTV> buttonEditor;
    SharedPtr<ButtonTV> buttonExit;
    SharedPtr<ButtonTV> buttonOptions;
    SharedPtr<ButtonSwitch> buttonLanguage;
    SharedPtr<ButtonTV> buttonCancel;
};
