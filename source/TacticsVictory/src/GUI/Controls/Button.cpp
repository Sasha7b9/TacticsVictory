#include <stdafx.h>
#include "Button.h"
#include "GUI/Cursor.h"
#include "Label.h"
#include "Hint.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ButtonRTS::ButtonRTS(Context *context) :
    Button(context)
{
    SetStyle("MainMenuButton");

    label = Label::Create("", true, SET::MENU::FONT::SIZE::ITEM);
    AddChild(label);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
ButtonRTS::ButtonRTS(UIElement *uielement, char *text, int width /* = -1 */, int height /* = -1 */) :
    Button(gContext)
{
    SetStyleAuto(gUIRoot->GetDefaultStyle());
    SetStyle("MainMenuButton");
    label = Label::Create(text, true, SET::MENU::FONT::SIZE::ITEM);
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

    SubscribeToEvent(this, E_HOVERBEGIN, URHO3D_HANDLER(ButtonRTS, HandleHoverBegin));
    SubscribeToEvent(this, E_HOVEREND, URHO3D_HANDLER(ButtonRTS, HandleHoverEnd));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ButtonRTS::RegisterObject(Context *context)
{
    context->RegisterFactory<ButtonRTS>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(Button);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ButtonRTS::SetText(char *text)
{
    label->SetText(text);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ButtonRTS::SetHint(char *text)
{
    hint = new Hint(text);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ButtonRTS::HandleHoverBegin(StringHash, VariantMap&)
{
    gCursor->SetSelected();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ButtonRTS::HandleHoverEnd(StringHash, VariantMap&)
{
    gCursor->SetNormal();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ButtonRTS::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor)
{
    Button::OnClickBegin(position, screenPosition, button, buttons, qualifiers, cursor);

    if(buttons == MOUSEB_RIGHT)
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
