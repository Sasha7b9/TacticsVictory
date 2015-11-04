#include <stdafx.h>


#include "WindowVariables.h"
#include "GUI/Elements/Label.h"
#include "GUI/Elements/GovernorFloat.h"


WindowVariables::WindowVariables(UContext *context) :
    lWindow(context)
{
    SetDefaultStyle(gCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    SetStyle("WindowNoBorder");

    SetLayout(Urho3D::LM_VERTICAL, 3, IntRect(3, 3, 3, 3));
    label = Label::Create("Variables", 8, 200, 20);
    label->SetPosition(0, 0);
    label->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_TOP);
    AddChild(label);

    SetFixedSize(GetWidth(), GetHeight());
}

void WindowVariables::SetVar(float *var_, char *title_)
{
    var = var_;
    title = title_;
}

void WindowVariables::AddFunctionFloat(char *title, pFuncFV funcRead, pFuncVF funcWrite)
{
    SharedPtr<GovernorFloat> governor(new GovernorFloat(gContext));
    AddChild(governor);
    governor->SetFunctionFloat(title, funcRead, funcWrite);
    SetFixedSize(governor->GetWidth() + 6, GetHeight() + governor->GetHeight() + 3);
}