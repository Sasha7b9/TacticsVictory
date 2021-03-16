// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Menu/WindowMenu.h"


class ButtonSwitch;


class MenuGame : public WindowMenu
{
    URHO3D_OBJECT(MenuGame, WindowMenu);

public:
    MenuGame(Context *);
    static void RegisterObject();

    void Open();
    void Close();

private:
    void HandleButtonRelease(StringHash, VariantMap&);  

    SharedPtr<ButtonT> buttonNewGame;
    SharedPtr<ButtonT> buttonEditor;
    SharedPtr<ButtonT> buttonExit;
    SharedPtr<ButtonT> buttonOptions;
    SharedPtr<ButtonSwitch> buttonLanguage;
    SharedPtr<ButtonT> buttonCancel;
};
