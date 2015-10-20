#include <stdafx.h>


#include "ButtonToggled.h"
#include "GUI/Elements/Label.h"


vButtonToggled::vButtonToggled(Context *context) :
    CheckBox(context)
{
    SetStyleAuto();
    label = vLabel::Create("", SET::MENU::FONT::SIZE::ITEM);
    AddChild(label);
}

vButtonToggled::vButtonToggled(UIElement * uielement, char * text, int width, int height) :
    CheckBox(gContext)
{
    label = vLabel::Create(text, SET::MENU::FONT::SIZE::ITEM);
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

void vButtonToggled::RegisterObject(Context *context)
{
    context->RegisterFactory<vButtonToggled>("UI");

    COPY_BASE_ATTRIBUTES(CheckBox);
}

void vButtonToggled::SetText(char *text)
{
    label->SetNewText(text);
}