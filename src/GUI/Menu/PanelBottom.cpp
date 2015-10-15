#include <stdafx.h>


tvPanelBottom::tvPanelBottom(Context *context) :
    tvWindow(context)
{
    SetName("PanelBottom");
    SetFixedSize(gSet->GetInt(TV_SCREEN_WIDTH), gSet->GetInt(TV_PANEL_BOTTOM_HEIGHT));
    SetMovable(false);
}

void tvPanelBottom::RegisterObject(Context *context)
{
    context->RegisterFactory<tvPanelBottom>("UI");

    COPY_BASE_ATTRIBUTES(tvWindow);
}
