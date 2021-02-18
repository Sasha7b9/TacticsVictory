// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Menu/TWindowMenu.h"


class MenuAboutMe : public WindowMenu
{
    URHO3D_OBJECT(MenuAboutMe, WindowMenu);

public:
    MenuAboutMe(Context *context = TheContext);

private:
    SharedPtr<TButton> buttonOk;

    void HandleButtonRelease(StringHash, VariantMap&);
};
