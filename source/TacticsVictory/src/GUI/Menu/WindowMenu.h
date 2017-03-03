#pragma once
#include "GUI/Controls/Window.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class WindowMenu : public WindowRTS
{
    URHO3D_OBJECT(WindowMenu, WindowRTS)

public:
    WindowMenu(Context *context = gContext);

protected:
    void SendEventReturn();
};

