#pragma once


#include "GUI/Elements/Window.h"


class lPanelBottom : public lWindow
{
    OBJECT(lPanelBottom);

public:
    lPanelBottom(Context *context = gContext);

    static void RegisterObject(Context *context = gContext);

private:
    lPanelBottom& operator=(const lPanelBottom&)
    {};
};