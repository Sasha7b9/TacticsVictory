// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Panels/PanelBottom.h"


PanelBottom::PanelBottom(Context *context) :
    WindowT(context)
{
    SetName("PanelBottom");
    SetFixedSize(TheSettings.GetInt("screen", "width"), TheSettings.GetInt("panel", "bottom", "height"));
    SetMovable(false);
}


void PanelBottom::RegisterObject()
{
    Context *context = TheContext;

    context->RegisterFactory<PanelBottom>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(WindowT);
}
