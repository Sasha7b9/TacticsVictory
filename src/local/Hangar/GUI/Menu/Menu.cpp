// 2021/04/12 23:30:24 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Menu/Menu.h"


bool Menus::IsActive()
{
    return ActiveMenu() != nullptr;
}


MenuPage *Menus::ActiveMenu()
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
