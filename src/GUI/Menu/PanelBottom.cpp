#include <stdafx.h>


#include "PanelBottom.h"


lPanelBottom::lPanelBottom(Context *context) :
    lWindow(context)
{
    SetName("PanelBottom");
    SetFixedSize(gSet->GetInt(TV_SCREEN_WIDTH), gSet->GetInt(TV_PANEL_BOTTOM_HEIGHT));
    SetMovable(false);
}

void lPanelBottom::RegisterObject(Context *context)
{
    context->RegisterFactory<lPanelBottom>("UI");

    COPY_BASE_ATTRIBUTES(lWindow);
}
