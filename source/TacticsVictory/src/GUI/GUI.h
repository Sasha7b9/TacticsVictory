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

    void Create();
    bool GheckOnDeadZoneForCursorBottomScreen(int x);
    bool MenuIsVisible();
    void SetVisibleMenu(bool visible);
    void SetVisibleMenu(WindowRTS *menuWindow, bool visible);
    bool UnderCursor();                                             // Возвращает true, если меню под курсором
    void RemoveFromScreen();
    void AddToScreen();
    void SetVisibleWindow(WindowRTS *window, bool visible);
    void SetUnvisibleAllWindows();

private:
    bool shownMenuMain = false;
    bool shownMenuOptions = false;

    void HandleMenuEvent(StringHash eventType, VariantMap& eventData);
};
