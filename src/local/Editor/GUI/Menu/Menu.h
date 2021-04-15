// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Menu/Menu_.h"


class PagePlay;
class PageStart;
class MenuPage;


class Menus : public MenuT
{
    URHO3D_OBJECT(Menus, MenuT);

public:

    Menus(Menus **self);

    void Hide();
    bool IsActive();
    bool ProcessingKey(int key);

private:

    SharedPtr<PageStart>  pageStart;

    void Open(MenuPage* page, MenuPage *prev);    // Открыть меню menu, при этом его хранителем указать prev
    void CloseAll();
    void HandleMenuEvent(StringHash, VariantMap&);
};
