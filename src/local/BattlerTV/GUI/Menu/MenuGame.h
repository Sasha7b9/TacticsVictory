// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Menu/WindowMenu.h"


class ButtonSwitch;


class MenuGame : public WindowMenu
{
    URHO3D_OBJECT(MenuGame, WindowMenu);

public:
    MenuGame(Context *context);
    static void RegisterObject();

    void Open();
    void Close();

private:
    void HandleButtonRelease(StringHash, VariantMap&);  

    SharedPtr<TButton> buttonNewGame;
    SharedPtr<TButton> buttonEditor;
    SharedPtr<TButton> buttonExit;
    SharedPtr<TButton> buttonOptions;
    SharedPtr<ButtonSwitch> buttonLanguage;
    SharedPtr<TButton> buttonCancel;
};
