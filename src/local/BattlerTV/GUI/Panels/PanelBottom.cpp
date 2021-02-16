// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


PanelBottom::PanelBottom(Context *context) :
    WindowRTS(context)
{
    SetName("PanelBottom");
    SetFixedSize(TheSet->GetInt(TV_SCREEN_WIDTH), TheSet->GetInt(TV_PANEL_BOTTOM_HEIGHT));
    SetMovable(false);
}


void PanelBottom::RegisterObject(Context *context)
{
    context->RegisterFactory<PanelBottom>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(WindowRTS);
}
