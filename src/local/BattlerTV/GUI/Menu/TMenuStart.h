// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUi/Controls/_TButtonSwitch.h"
#include "GUI/Menu/TWindowMenu.h"


class MenuStart : public WindowMenu
{
    URHO3D_OBJECT(MenuStart, WindowMenu);

public:
    MenuStart(Context *context = TheContext);
    ~MenuStart();

private:
    void HandleButtonRelease(StringHash, VariantMap&);

    SharedPtr<TButton> buttonServer;
    SharedPtr<TButton> buttonClient;
    SharedPtr<TButton> buttonEditor;
    SharedPtr<TButton> buttonExit;
    SharedPtr<TButton> buttonOptions;
    SharedPtr<TButton> buttonHelp;
    SharedPtr<TButton> buttonAboutGame;
    SharedPtr<TButton> buttonAboutMe;
    SharedPtr<ButtonSwitch> buttonLanguage;
};
