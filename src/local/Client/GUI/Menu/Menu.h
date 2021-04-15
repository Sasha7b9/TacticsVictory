// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Menu/Menu_.h"
#include "GUI/Menu/PageFindServer.h"


class PageAboutMe;
class PageOptions;
class PagePlay;
class PageStart;
class MenuPage;


class Menus : public MenuT
{
    URHO3D_OBJECT(Menus, MenuT);

public:

    Menus(Menus **self);

    void Hide();
    bool ProcessingKey(int key);

    SharedPtr<PageFindServer> pageFindServer;

private:

    SharedPtr<PageStart>      pageStart;
    SharedPtr<PageAboutMe>    pageAbout;
    SharedPtr<PagePlay>       pagePlay;
    SharedPtr<PageOptions>    pageOptions;

    void Open(MenuPage* page, MenuPage *prev);    // Открыть меню menu, при этом его хранителем указать prev
    void CloseAll();
    void HandleMenuEvent(StringHash, VariantMap&);
};
