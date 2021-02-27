// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Controls/ButtonSwitch_.h"
#include "GUI/Menu/MenuEvents.h"
#include "GUI/Menu/MenuStart.h"


WindowMenu::WindowMenu(Context *context) : WindowT(context)
{

}


void WindowMenu::SendEventClose()
{
    using namespace MenuEvent;

    VariantMap eventData = GetEventDataMap();
    eventData[P_TYPE] = ME_Close;
    eventData[P_SOURCE] = this;
    eventData[P_DESTINATION] = prevMenu;
    SendEvent(E_MENU, eventData);
}


void WindowMenu::Open(WindowMenu *prev)
{
    prevMenu = prev;
    TheUIRoot->AddChild(this);
}


void WindowMenu::Close()
{
    TheUIRoot->RemoveChild(this);
}


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


void WindowMenu::SetFocusedNext()
{
    int numButton = (NumFocusedButton() + 1) % (int)buttons.Size();
    buttons[(uint)numButton]->SetFocus(true);
}


void WindowMenu::SetFocusedPrev()
{
    int numButton = NumFocusedButton() - 1;
    if (numButton < 0)
    {
        numButton = (int)buttons.Size() - 1;
    }
    buttons[(uint)numButton]->SetFocus(true);
}


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
