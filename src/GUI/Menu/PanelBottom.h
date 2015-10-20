#pragma once


#include "GUI/Elements/Window.h"


class vPanelBottom : public vWindow
{
    OBJECT(vPanelBottom);

public:
    vPanelBottom(Context *context);

    static void RegisterObject(Context *context);

private:
    vPanelBottom& operator=(const vPanelBottom&)
    {};
};