#include <stdafx.h>


#include "Button.h"
#include "GUI/Elements/Cursor.h"
#include "GUI/Elements/Label.h"


vButton::vButton(Context *context) :
    Button(context)
{
    SetStyle("MainMenuButton");

    label = vLabel::Create("", SET::MENU::FONT::SIZE::ITEM);
    AddChild(label);
}

vButton::vButton(UIElement *uielement, char *text, int width /* = -1 */, int height /* = -1 */) :
    Button(gContext)
{
    SetStyle("MainMenuButton");
    label = vLabel::Create(text, SET::MENU::FONT::SIZE::ITEM);
    AddChild(label);

    if (uielement)
    {
        uielement->AddChild(this);
    }

    if (width == -1 && height == -1)
    {

    }
    else if (width == -1)
    {
        SetFixedHeight(height);
    }
    else if (height == -1)
    {
        SetFixedWidth(width);
    }
    else
    {
        SetFixedSize(width, height);
    }

    SubscribeToEvent(this, E_HOVERBEGIN, HANDLER(vButton, HandleHoverBegin));
    SubscribeToEvent(this, E_HOVEREND, HANDLER(vButton, HandleHoverEnd));
    SubscribeToEvent(this, E_MOUSEBUTTONDOWN, HANDLER(vButton, HandleMouseDown));
}

void vButton::RegisterObject(Context *context)
{
    context->RegisterFactory<vButton>("UI");

    COPY_BASE_ATTRIBUTES(Button);
}

void vButton::SetText(char *text)
{
    label->SetNewText(text);
}

void vButton::HandleHoverBegin(StringHash, VariantMap&)
{
    gCursor->SetSelected();
}

void vButton::HandleHoverEnd(StringHash, VariantMap&)
{
    gCursor->SetNormal();
}

void vButton::HandleMouseDown(StringHash, VariantMap&)
{
    gCursor->SetSelected();
}