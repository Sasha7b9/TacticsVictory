// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Menu/MenuPage_.h"


class ButtonSwitch;


class MenuGame : public MenuPage
{
    URHO3D_OBJECT(MenuGame, MenuPage);

public:
    MenuGame(Context *);
    static void RegisterObject();

    void Open();
    void Close();

private:
    void HandleButtonRelease(StringHash, VariantMap&);  

    SharedPtr<ButtonT>      buttonNewGame;
    SharedPtr<ButtonT>      buttonExit;
    SharedPtr<ButtonT>      buttonOptions;
    SharedPtr<ButtonT>      buttonCancel;
};
