// 2021/04/12 23:30:24 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Menu/Menu.h"


Menus::Menus(Menus **self) : MenuT((MenuT **)self)
{
    *self = this;
}


bool Menus::ProcessingKey(int /*key*/)
{
    return false;
}
