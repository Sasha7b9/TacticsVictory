#pragma once


#include "GUI/Elements/Window.h"


class PanelBottom : public lWindow
{
    OBJECT(PanelBottom);

public:
    PanelBottom(UContext *context = gContext);

    static void RegisterObject(UContext *context = gContext);

private:
    PanelBottom& operator=(const PanelBottom&)
    {};
};