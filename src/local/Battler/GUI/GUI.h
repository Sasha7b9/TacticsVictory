// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Menu/MenuEvents.h"



class WindowRTS;



class GUI : public Object
{
    URHO3D_OBJECT(GUI, Object);

public:
    GUI();
    ~GUI();

    bool GheckOnDeadZoneForCursorBottomScreen(int x);
    bool UnderCursor();                                             // Возвращает true, если меню под курсором
    void SetVisibleWindow(WindowRTS *window, bool visible);
    void SetUnvisibleAllWindows();

private:
    void Create();
    void RegistrationObjects();

    DEFAULT_MEMBERS(GUI);
};
