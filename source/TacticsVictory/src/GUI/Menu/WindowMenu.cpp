#include "stdafx.h"
#include "MenuEvents.h"
#include "WindowMenu.h"
#include "GUI/Controls/Button.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WindowMenu::WindowMenu(Context *context) : WindowRTS(context)
{

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void WindowMenu::SendEventReturn()
{
    VariantMap eventData = GetEventDataMap();
    eventData[MenuEvent::P_TYPE] = MenuEvent_Return;
    SendEvent(E_MENU, eventData);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void WindowMenu::Open()
{
    gUIRoot->AddChild(this);
    this->SetFocus(true);
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(WindowMenu, HandleKeyDown));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void WindowMenu::Close()
{
    gUIRoot->RemoveChild(this);
    SendEventReturn();
    UnsubscribeFromEvent(E_KEYDOWN);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void WindowMenu::HandleKeyDown(StringHash, VariantMap& eventData)
{
    using namespace KeyDown;

    int key = eventData[P_KEY].GetInt();

    if (key == KEY_UP || key == KEY_LEFT)
    {
        SetFocusedPrev();
    }
    else if (key == KEY_DOWN || key == KEY_RIGHT)
    {
        SetFocusedNext();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void WindowMenu::SetFocusedNext()
{
    int numButton = (NumFocusedButton() + 1) % (int)buttons.Size();
    buttons[(uint)numButton]->SetFocus(true);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void WindowMenu::SetFocusedPrev()
{
    int numButton = NumFocusedButton() - 1;
    if (numButton < 0)
    {
        numButton = (int)buttons.Size() - 1;
    }
    buttons[(uint)numButton]->SetFocus(true);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int WindowMenu::NumFocusedButton()
{
    for (uint i = 0; i < buttons.Size(); i++)
    {
        if (buttons[i]->HasFocus())
        {
            return (int)i;
        }
    }
    return -1;
}
