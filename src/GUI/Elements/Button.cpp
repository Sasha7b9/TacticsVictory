#include <stdafx.h>


#include "Button.h"
#include "GUI/Elements/Cursor.h"
#include "GUI/Elements/Label.h"
#include "GUI/Elements/Hint.h"


lButton::lButton(Context *context) :
    Button(context)
{
    SetStyle("MainMenuButton");

    label = lLabel::Create("", SET::MENU::FONT::SIZE::ITEM);
    AddChild(label);
}

lButton::lButton(UIElement *uielement, char *text, int width /* = -1 */, int height /* = -1 */) :
    Button(gContext)
{
    SetStyle("MainMenuButton");
    label = lLabel::Create(text, SET::MENU::FONT::SIZE::ITEM);
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

    SubscribeToEvent(this, Urho3D::E_HOVERBEGIN, HANDLER(lButton, HandleHoverBegin));
    SubscribeToEvent(this, Urho3D::E_HOVEREND, HANDLER(lButton, HandleHoverEnd));
    SubscribeToEvent(this, Urho3D::E_MOUSEBUTTONDOWN, HANDLER(lButton, HandleMouseDown));
}

void lButton::RegisterObject(Context *context)
{
    context->RegisterFactory<lButton>("UI");

    COPY_BASE_ATTRIBUTES(Button);
}

void lButton::SetText(char *text)
{
    label->SetNewText(text);
}

void lButton::SetHint(char *text)
{
    hint = new lHint(text);
}

void lButton::HandleHoverBegin(StringHash, VariantMap&)
{
    gCursor->SetSelected();
}

void lButton::HandleHoverEnd(StringHash, VariantMap&)
{
    gCursor->SetNormal();
}

void lButton::HandleMouseDown(StringHash, VariantMap&)
{
    gCursor->SetSelected();
}

void lButton::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor)
{
    Button::OnClickBegin(position, screenPosition, button, buttons, qualifiers, cursor);

    if(buttons == Urho3D::MOUSEB_RIGHT)
    {
        if(hint)
        {
            if(gHint)
            {
                gUIRoot->RemoveChild(gHint);
            }
            hint->SetPosition(screenPosition.x_, screenPosition.y_ - hint->GetHeight());
            gUIRoot->AddChild(hint);
            hint->BringToFront();
            gHint = hint;
            gCounterHint = 0;
        }
    }
}
