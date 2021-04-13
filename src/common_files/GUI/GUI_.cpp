// 2021/04/13 11:26:09 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/GUI_.h"


GUIT::GUIT(GUIT **self) : Object(TheContext)
{
    *self = this;
}


bool GUIT::UnderCursor()
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
