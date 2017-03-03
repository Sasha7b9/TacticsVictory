#pragma once
#include "GUI/Menu/MenuEvents.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class WindowRTS;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GUI : public Object
{
    URHO3D_OBJECT(GUI, Object);

public:
    GUI();
    ~GUI();

    static void RegistrationObjects();

    void Create();
    bool GheckOnDeadZoneForCursorBottomScreen(int x);
    bool UnderCursor();                                             // Возвращает true, если меню под курсором
    void RemoveFromScreen();
    void AddToScreen();
    void SetVisibleWindow(WindowRTS *window, bool visible);
    void SetUnvisibleAllWindows();

private:
    bool shownMenuMain = false;
    bool shownMenuOptions = false;
};
