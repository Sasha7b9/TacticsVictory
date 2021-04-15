// 2021/04/12 23:30:01 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Menu/Menu_.h"
#include "GUI/Menu/MenuPage_.h"


class Menus : public MenuT
{
    URHO3D_OBJECT(Menus, MenuT);

public:

    Menus(Menus **self);

    bool ProcessingKey(int key);

private:
};