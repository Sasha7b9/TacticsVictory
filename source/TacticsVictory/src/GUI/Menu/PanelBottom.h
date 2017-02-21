#pragma once


#include "GUI/Elements/Window.h"


class PanelBottom : public WindowRTS
{
    URHO3D_OBJECT(PanelBottom, WindowRTS);

public:
    PanelBottom(Context *context = gContext);

    static void RegisterObject(Context *context = gContext);

private:
    PanelBottom& operator=(const PanelBottom&)
    {};
};