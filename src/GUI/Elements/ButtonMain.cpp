#include <stdafx.h>


#include "ButtonMain.h"
#include "GUI/Elements/Cursor.h"
#include "GUI/Elements/Label.h"
#include "GUI/Elements/Hint.h"


ButtonMain::ButtonMain(Context *context) :
    Urho3D::Button(context)
{
    SetStyle("MainMenuButton");

    label = Label::Create("", SET::MENU::FONT::SIZE::ITEM);
    AddChild(label);
}

ButtonMain::ButtonMain(UIElement *uielement, char *text, int width /* = -1 */, int height /* = -1 */) :
    Urho3D::Button(gContext)
{
    //SetStyleAuto(gUIRoot->GetDefaultStyle());
    SetStyle("MainMenuButton");
    label = Label::Create(text, SET::MENU::FONT::SIZE::ITEM);
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

    SubscribeToEvent(this, Urho3D::E_HOVERBEGIN, HANDLER(ButtonMain, HandleHoverBegin));
    SubscribeToEvent(this, Urho3D::E_HOVEREND, HANDLER(ButtonMain, HandleHoverEnd));
}

void ButtonMain::RegisterObject(Context *context)
{
    context->RegisterFactory<ButtonMain>("UI");

    COPY_BASE_ATTRIBUTES(Urho3D::Button);
}

void ButtonMain::SetText(char *text)
{
    label->SetText(text);
}

void ButtonMain::SetHint(char *text)
{
    hint = new Hint(text);
}

void ButtonMain::HandleHoverBegin(StringHash, VariantMap&)
{
    gCursor->SetSelected();
}

void ButtonMain::HandleHoverEnd(StringHash, VariantMap&)
{
    gCursor->SetNormal();
}

void ButtonMain::OnClickBegin(const UIntVector2& position, const UIntVector2& screenPosition, int button, int buttons, int qualifiers, UCursor* cursor)
{
    Urho3D::Button::OnClickBegin(position, screenPosition, button, buttons, qualifiers, cursor);

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
