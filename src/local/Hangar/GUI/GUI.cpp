// 2021/04/12 22:58:35 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


GUI::GUI(GUI **self) : Object(TheContext)
{
    RegistrationObjects();
    Create();

    *self = this;
}


void GUI::RegistrationObjects()
{

}


void GUI::Create()
{
    TheChat = new Chat();
    TheUIRoot->AddChild(TheChat);
}


bool GUI::UnderCursor()
{
    PODVector<UIElement *> elements;
    TheUIRoot->GetChildren(elements);

    for (UIElement *elem : elements)
    {
        if (elem->GetName() != "Cursor" && elem->IsVisible() && elem->IsInside(TheCursor->GetCursor()->GetPosition(), true))
        {
            return true;
        }
    }

    return false;
}
