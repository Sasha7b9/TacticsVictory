// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdafx.h>
#include "WindowVariables.h"
#include "GUI/Controls/Label.h"
#include "GUI/Controls/GovernorFloat.h"



WindowVariables::WindowVariables(Context *context) :
    WindowRTS(context)
{
    SetDefaultStyle(gCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    SetStyle("WindowNoBorder");

    SetLayout(LM_VERTICAL, 3, IntRect(3, 3, 3, 3));
    label = Label::Create("Variables", true, 8, 200, 20);
    label->SetPosition(0, 0);
    label->SetAlignment(HA_CENTER, VA_TOP);
    AddChild(label);

    SetFixedSize(GetWidth(), GetHeight());
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void WindowVariables::SetVar(float *var_, char *title_)
{
    var = var_;
    title = title_;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void WindowVariables::AddFunctionFloat(char *title_, pFuncFV funcRead, pFuncVF funcWrite)
{
    SharedPtr<GovernorFloat> governor_(new GovernorFloat(gContext));
    AddChild(governor_);
    governor_->SetFunctionFloat(title_, funcRead, funcWrite);
    SetFixedSize(governor_->GetWidth() + 6, GetHeight() + governor_->GetHeight() + 3);
}
