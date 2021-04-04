// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Controls/Label_.h"
#include "GUI/Controls/Buttons/ButtonToggled_.h"


ButtonToggled::ButtonToggled(Context *context) :
    CheckBox(context)
{
    SetStyleAuto();
    label = Label::Create("", true, TheSettings.GetInt("menu", "font", "size", "item"));
    AddChild(label);
}


ButtonToggled::ButtonToggled(UIElement * uielement, char * text, int width, int height) :
    CheckBox(TheContext)
{
    SetStyleAuto(TheUIRoot->GetDefaultStyle());
    label = Label::Create(text, true, TheSettings.GetInt("menu", "font", "size", "item"));
    AddChild(label);

    if(uielement)
    {
        uielement->AddChild(this);
    }

    if(width == -1 && height == -1)
    {

    }
    else if(width == -1)
    {
        SetFixedHeight(height);
    }
    else if(height == -1)
    {
        SetFixedWidth(width);
    }
    else
    {
        SetFixedSize(width, height);
    }
}


void ButtonToggled::RegisterObject()
{
    TheContext->RegisterFactory<ButtonToggled>("UI");

    Context *context = TheContext;

    URHO3D_COPY_BASE_ATTRIBUTES(CheckBox);
}


void ButtonToggled::SetText(char *text)
{
    label->SetText(text);
}
