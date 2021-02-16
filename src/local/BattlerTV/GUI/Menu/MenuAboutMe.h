// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Menu/WindowMenu.h"


class MenuAboutMe : public WindowMenu
{
    URHO3D_OBJECT(MenuAboutMe, WindowMenu);

public:
    MenuAboutMe(Context *context = TheContext);

private:
    SharedPtr<ButtonRTS> buttonOk;

    void HandleButtonRelease(StringHash, VariantMap&);
};
