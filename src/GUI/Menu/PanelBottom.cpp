#include <stdafx.h>


#include "PanelBottom.h"


PanelBottom::PanelBottom(UContext *context) :
    lWindow(context)
{
    SetName("PanelBottom");
    SetFixedSize(gSet->GetInt(TV_SCREEN_WIDTH), gSet->GetInt(TV_PANEL_BOTTOM_HEIGHT));
    SetMovable(false);
}

void PanelBottom::RegisterObject(UContext *context)
{
    context->RegisterFactory<PanelBottom>("UI");

    COPY_BASE_ATTRIBUTES(lWindow);
}
