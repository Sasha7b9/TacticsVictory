#include <stdafx.h>


#include "ButtonToggled.h"


tvButtonToggled::tvButtonToggled(Context *context) :
    CheckBox(context)
{
    SetStyleAuto();
    label = tvLabel::Create("", SET::MENU::FONT::SIZE::ITEM);
    AddChild(label);
}

tvButtonToggled::tvButtonToggled(UIElement * uielement, char * text, int width, int height) :
    CheckBox(gContext)
{
    label = tvLabel::Create(text, SET::MENU::FONT::SIZE::ITEM);
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

void tvButtonToggled::RegisterObject(Context *context)
{
    context->RegisterFactory<tvButtonToggled>("UI");

    COPY_BASE_ATTRIBUTES(CheckBox);
}

void tvButtonToggled::SetText(char *text)
{
    label->SetNewText(text);
}