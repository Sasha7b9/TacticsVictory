// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Controls/Buttons/ButtonSwitch_.h"
#include "GUI/Menu/MenuPage_.h"


MenuPage::MenuPage() : WindowT(TheContext)
{

}


void MenuPage::SendEventClose()
{
    using namespace MenuEvent;

    VariantMap eventData = GetEventDataMap();
    eventData[P_TYPE] = ME_CLOSE;
    eventData[P_SOURCE] = this;
    eventData[P_DESTINATION] = prev_menu;
    SendEvent(E_MENU, eventData);
}


void MenuPage::Open(MenuPage *prev)
{
    if (prev)
    {
        prev_menu = prev;
    }

    TheUIRoot->AddChild(this);
}


void MenuPage::Close()
{
    TheUIRoot->RemoveChild(this);
}


void MenuPage::ProcessingKey(int key)
{
    if(KEY_IS_ESC)
    {
        SendEventClose();
    }
    else if (KEY_IS_UP || KEY_IS_LEFT)
    {
        SetFocusedPrev();
    }
    else if (KEY_IS_DOWN || KEY_IS_RIGHT)
    {
        SetFocusedNext();
    }
}


void MenuPage::SetFocusedNext()
{
    int numButton = (NumFocusedButton() + 1) % (int)buttons.Size();
    buttons[(uint)numButton]->SetFocus(true);
}


void MenuPage::SetFocusedPrev()
{
    int numButton = NumFocusedButton() - 1;
    if (numButton < 0)
    {
        numButton = (int)buttons.Size() - 1;
    }
    buttons[(uint)numButton]->SetFocus(true);
}


int MenuPage::NumFocusedButton()
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
