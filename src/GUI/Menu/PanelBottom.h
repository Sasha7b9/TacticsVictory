#pragma once


#include "GUI/Elements/Window.h"


class lPanelBottom : public lWindow
{
    OBJECT(lPanelBottom);

public:
    lPanelBottom(Context *context);

    static void RegisterObject(Context *context);

private:
    lPanelBottom& operator=(const lPanelBottom&)
    {};
};