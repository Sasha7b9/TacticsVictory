#include <stdafx.h>


#include "ButtonToggled.h"
#include "GUI/Elements/Label.h"


ButtonToggled::ButtonToggled(UContext *context) :
    UCheckBox(context)
{
    SetStyleAuto();
    label = Label::Create("", SET::MENU::FONT::SIZE::ITEM);
    AddChild(label);
}

ButtonToggled::ButtonToggled(UIElement * uielement, char * text, int width, int height) :
    UCheckBox(gContext)
{
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

void ButtonToggled::RegisterObject(UContext *context)
{
    context->RegisterFactory<ButtonToggled>("UI");

    COPY_BASE_ATTRIBUTES(UCheckBox);
}

void ButtonToggled::SetText(char *text)
{
    label->SetText(text);
}