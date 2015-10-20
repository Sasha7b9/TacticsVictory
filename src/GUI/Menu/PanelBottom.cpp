#include <stdafx.h>


#include "PanelBottom.h"


vPanelBottom::vPanelBottom(Context *context) :
    vWindow(context)
{
    SetName("PanelBottom");
    SetFixedSize(gSet->GetInt(TV_SCREEN_WIDTH), gSet->GetInt(TV_PANEL_BOTTOM_HEIGHT));
    SetMovable(false);
}

void vPanelBottom::RegisterObject(Context *context)
{
    context->RegisterFactory<vPanelBottom>("UI");

    COPY_BASE_ATTRIBUTES(vWindow);
}
