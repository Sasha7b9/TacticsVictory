#pragma once
#include "GUI/Controls/Window.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class WindowAboutMe : public WindowRTS
{
    URHO3D_OBJECT(WindowAboutMe, WindowRTS);

public:
    WindowAboutMe(Context *context = gContext);

private:
    void HandleButtonRelease(StringHash, VariantMap&);
    virtual void HandleKeyDown(StringHash, VariantMap&);

    SharedPtr<ButtonRTS> buttonOk;
};
