#include <stdafx.h>


#include "ButtonToggled.h"
#include "GUI/Elements/Label.h"


ButtonToggled::ButtonToggled(Context *context) :
    CheckBox(context)
{
    SetStyleAuto();
    label = Label::Create("", SET::MENU::FONT::SIZE::ITEM);
    AddChild(label);
}

ButtonToggled::ButtonToggled(UIElement * uielement, char * text, int width, int height) :
    CheckBox(gContext)
{
    SetStyleAuto(gUIRoot->GetDefaultStyle());
    label = Label::Create(text, SET::MENU::FONT::SIZE::ITEM);
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

void ButtonToggled::RegisterObject(Context *context)
{
    context->RegisterFactory<ButtonToggled>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(CheckBox);
}

void ButtonToggled::SetText(char *text)
{
    label->SetText(text);
}