#pragma once


#include "GUI/Elements/Window.h"


class PanelBottom : public lWindow
{
    URHO3D_OBJECT(PanelBottom, lWindow);

public:
    PanelBottom(Context *context = gContext);

    static void RegisterObject(Context *context = gContext);

private:
    PanelBottom& operator=(const PanelBottom&)
    {};
};