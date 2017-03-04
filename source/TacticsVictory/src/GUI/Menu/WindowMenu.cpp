#include "stdafx.h"
#include "MenuEvents.h"
#include "WindowMenu.h"
#include "GUI/Controls/Button.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WindowMenu::WindowMenu(Context *context) : WindowRTS(context)
{

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void WindowMenu::SendEventClose()
{
    using namespace MenuEvent;

    VariantMap eventData = GetEventDataMap();
    eventData[P_TYPE] = MenuEvent_Close;
    eventData[P_SOURCE] = this;
    eventData[P_DESTINATION] = prevMenu;
    SendEvent(E_MENU, eventData);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void WindowMenu::Open(WindowMenu *prev)
{
    prevMenu = prev;
    gUIRoot->AddChild(this);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void WindowMenu::Close()
{
    gUIRoot->RemoveChild(this);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void WindowMenu::ProcessingKey(int key)
{
    if(KEY_IS_ESC)
    {
        SendEventClose();
    }
    if (KEY_IS_UP || KEY_IS_LEFT)
    {
        SetFocusedPrev();
    }
    else if (KEY_IS_DOWN || KEY_IS_RIGHT)
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
