#pragma once


#include "GUI/Elements/Window.h"


class PanelBottom : public lWindow
{
    OBJECT(PanelBottom);

public:
    PanelBottom(Context *context = gContext);

    static void RegisterObject(Context *context = gContext);

private:
    PanelBottom& operator=(const PanelBottom&)
    {};
};