#include <stdafx.h>


#include "WindowVariables.h"
#include "GUI/Elements/Label.h"
#include "GUI/Elements/GovernorFloat.h"


vWindowVariables::vWindowVariables(Context *context) :
    vWindow(context)
{
    SetDefaultStyle(gCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    SetStyle("WindowNoBorder");

    SetLayout(Urho3D::LM_VERTICAL, 3, IntRect(3, 3, 3, 3));
    label = vLabel::Create("Variables", 8, 200, 20);
    label->SetPosition(0, 0);
    label->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_CENTER);
    AddChild(label);

    SetFixedSize(GetWidth(), GetHeight());
}

void vWindowVariables::SetVar(float *var_, char *title_)
{
    var = var_;
    title = title_;
}

void vWindowVariables::AddFunctionFloat(char *title, pFuncFV funcRead, pFuncVF funcWrite)
{
    SharedPtr<vGovernorFloat> governor(new vGovernorFloat(gContext));
    AddChild(governor);
    governor->SetFunctionFloat(title, funcRead, funcWrite);
    SetFixedSize(governor->GetWidth() + 6, GetHeight() + governor->GetHeight() + 3);
}