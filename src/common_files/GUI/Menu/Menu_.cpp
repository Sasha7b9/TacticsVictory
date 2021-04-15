// 2021/04/15 14:22:37 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Menu/Menu_.h"
#include "GUI/Menu/MenuPage_.h"


MenuT::MenuT(MenuT **self) : Object(TheContext)
{
    *self = this;
}


bool MenuT::IsActive()
{
    return ActiveMenu() != nullptr;
}


MenuPage *MenuT::ActiveMenu()
{
    for (MenuPage *window : allMenus)
    {
        if (window->GetParent())
        {
            return window;
        }
    }

    return nullptr;
}
