#include <stdafx.h>


#include "PanelBottom.h"


PanelBottom::PanelBottom(Context *context) :
    WindowRTS(context)
{
    SetName("PanelBottom");
    SetFixedSize(gSet->GetInt(TV_SCREEN_WIDTH), gSet->GetInt(TV_PANEL_BOTTOM_HEIGHT));
    SetMovable(false);
}

void PanelBottom::RegisterObject(Context *context)
{
    context->RegisterFactory<PanelBottom>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(WindowRTS);
}
