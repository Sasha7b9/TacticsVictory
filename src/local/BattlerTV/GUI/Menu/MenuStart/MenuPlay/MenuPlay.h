// 2021/03/16 21:50:02 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Menu/WindowMenu.h"


class MenuPlay : public WindowMenu
{
    URHO3D_OBJECT(MenuPlay, WindowMenu);

public:
    MenuPlay();

private:

    SharedPtr<ButtonT> buttonFindServer;    // "Найти сервер"
    SharedPtr<ButtonT> buttonCreateServer;  // "Создать сервер"
    SharedPtr<ButtonT> buttonBack;          // Вернуться в предыдущее меню

    void HandleButtonRelease(StringHash, VariantMap &);
};
