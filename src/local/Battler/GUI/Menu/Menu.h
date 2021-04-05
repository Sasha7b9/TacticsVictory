// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class MenuAboutMe;
class MenuOptions;
class MenuStart;
class MenuPage;


class Menu
{
public:

    static void Create();
    static void Hide();
    static bool IsActive();
    static bool ProcessingKey(int key);

private:

    static MenuPage* ActiveMenu();
    static void Open(MenuPage* menu, MenuPage *prev);    // Открыть меню menu, при этом его хранителем указать prev
    static void CloseAll();
    static void HandleMenuEvent(StringHash, VariantMap&);
};
