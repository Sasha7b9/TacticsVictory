#pragma once
#include "GUI/Menu/WindowMenu.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MenuAboutMe : public WindowMenu
{
    URHO3D_OBJECT(MenuAboutMe, WindowMenu);

public:
    MenuAboutMe(Context *context = gContext);

private:
    SharedPtr<ButtonRTS> buttonOk;

    void HandleButtonRelease(StringHash, VariantMap&);

    DEFAULT_MEMBERS(MenuAboutMe);
};
