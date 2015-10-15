#include <stdafx.h>


tvButton::tvButton(Context *context) :
    Button(context)
{
    SetStyle("MainMenuButton");

    label = tvLabel::Create("", SET::MENU::FONT::SIZE::ITEM);
    AddChild(label);
}

tvButton::tvButton(UIElement *uielement, char *text, int width /* = -1 */, int height /* = -1 */) :
    Button(gContext)
{
    SetStyle("MainMenuButton");
    label = tvLabel::Create(text, SET::MENU::FONT::SIZE::ITEM);
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

    SubscribeToEvent(this, E_HOVERBEGIN, HANDLER(tvButton, HandleHoverBegin));
    SubscribeToEvent(this, E_HOVEREND, HANDLER(tvButton, HandleHoverEnd));
    SubscribeToEvent(this, E_MOUSEBUTTONDOWN, HANDLER(tvButton, HandleMouseDown));
}

void tvButton::RegisterObject(Context *context)
{
    context->RegisterFactory<tvButton>("UI");

    COPY_BASE_ATTRIBUTES(Button);
}

void tvButton::SetText(char *text)
{
    label->SetNewText(text);
}

void tvButton::HandleHoverBegin(StringHash, VariantMap&)
{
    gCursor->SetSelected();
}

void tvButton::HandleHoverEnd(StringHash, VariantMap&)
{
    gCursor->SetNormal();
}

void tvButton::HandleMouseDown(StringHash, VariantMap&)
{
    gCursor->SetSelected();
}