#pragma once
#include "GUI/Controls/Window.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MenuAboutMe : public WindowRTS
{
    URHO3D_OBJECT(MenuAboutMe, WindowRTS);

public:
    MenuAboutMe(Context *context = gContext);

private:
    void HandleButtonRelease(StringHash, VariantMap&);
    virtual void HandleKeyDown(StringHash, VariantMap&);

    SharedPtr<ButtonRTS> buttonOk;
};
