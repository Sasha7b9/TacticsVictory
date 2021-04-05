// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class MenuAboutMe;
class MenuOptions;
class MenuStart;
class WindowMenu;


class Menu
{
public:

    static void Create();
    static void Hide();
    static bool IsActive();
    static bool ProcessingKey(int key);

private:

    static WindowMenu* ActiveMenu();
    static void Open(WindowMenu* menu, WindowMenu *prev);    // Открыть меню menu, при этом его хранителем указать prev
    static void CloseAll();
    static void HandleMenuEvent(StringHash, VariantMap&);
};
