#include <stdafx.h>


#include "ButtonToggled.h"
#include "GUI/Elements/Label.h"


lButtonToggled::lButtonToggled(Context *context) :
    CheckBox(context)
{
    SetStyleAuto();
    label = lLabel::Create("", SET::MENU::FONT::SIZE::ITEM);
    AddChild(label);
}

lButtonToggled::lButtonToggled(UIElement * uielement, char * text, int width, int height) :
    CheckBox(gContext)
{
    label = lLabel::Create(text, SET::MENU::FONT::SIZE::ITEM);
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

void lButtonToggled::RegisterObject(Context *context)
{
    context->RegisterFactory<lButtonToggled>("UI");

    COPY_BASE_ATTRIBUTES(CheckBox);
}

void lButtonToggled::SetText(char *text)
{
    label->SetNewText(text);
}