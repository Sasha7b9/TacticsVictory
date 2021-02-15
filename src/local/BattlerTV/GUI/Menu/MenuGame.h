// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Menu/WindowMenu.h"



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

    SharedPtr<ButtonRTS> buttonNewGame;
    SharedPtr<ButtonRTS> buttonEditor;
    SharedPtr<ButtonRTS> buttonExit;
    SharedPtr<ButtonRTS> buttonOptions;
    SharedPtr<ButtonSwitch> buttonLanguage;
    SharedPtr<ButtonRTS> buttonCancel;

    DEFAULT_MEMBERS(MenuGame);
};
