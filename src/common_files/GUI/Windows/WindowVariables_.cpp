// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Controls/GovernorFloat_.h"
#include "GUI/Controls/Label_.h"
#include "GUI/Windows/WindowVariables_.h"


WindowVariables::WindowVariables() : WindowT(TheContext)
{
    SetDefaultStyle(TheCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    SetStyle("WindowNoBorder");

    SetLayout(LM_VERTICAL, 3, IntRect(3, 3, 3, 3));
    label = Label::Create("Variables", 8, 200, 20);
    label->SetPosition(0, 0);
    label->SetAlignment(HA_CENTER, VA_TOP);
    AddChild(label);

    SetFixedSize(GetWidth(), GetHeight());
}


void WindowVariables::SetVar(float *var_, char *title_)
{
    var = var_;
    title = title_;
}


void WindowVariables::AddFunctionFloat(char *title_, pFuncFV funcRead, pFuncVF funcWrite)
{
    SharedPtr<GovernorFloat> governor_(new GovernorFloat(TheContext));
    AddChild(governor_);
    governor_->SetFunctionFloat(title_, funcRead, funcWrite);
    SetFixedSize(governor_->GetWidth() + 6, GetHeight() + governor_->GetHeight() + 3);
}
