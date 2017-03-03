﻿#include "stdafx.h"
#include "MenuEvents.h"
#include "WindowMenu.h"
#include "GUI/Controls/Button.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WindowMenu::WindowMenu(Context *context, WindowMenu *prev) : WindowRTS(context), prevMenu(prev)
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
void WindowMenu::Open()
{
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
    if(key == KEY_ESCAPE)
    {
        SendEventClose();
    }
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
