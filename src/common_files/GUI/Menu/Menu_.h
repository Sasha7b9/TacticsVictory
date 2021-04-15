// 2021/04/15 14:21:19 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class MenuPage;


class MenuT : public Object
{
    URHO3D_OBJECT(MenuT, Object);

public:

    MenuT(MenuT **self);

    bool IsActive();

protected:

    MenuPage *ActiveMenu();

    PODVector<MenuPage *>  allMenus;       // Здесь список всех меню
};
