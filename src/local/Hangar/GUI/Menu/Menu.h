// 2021/04/12 23:30:01 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Menu/MenuPage_.h"


class Menus : public Object
{
    URHO3D_OBJECT(Menus, Object);

public:

    Menus(Menus **self);

    bool IsActive();
    bool ProcessingKey(int key);

private:

    PODVector<MenuPage *> allMenus;

    MenuPage *ActiveMenu();
};