#pragma once


#include "GUI/Menu/MenuEvents.h"


class lWindow;


class lGUI : public Object
{
    OBJECT(lGUI);

public:
    lGUI();
    ~lGUI();

    void Create();
    bool GheckOnDeadZoneForCursorBottomScreen(int x);
    bool MenuIsVisible();
    void SetVisibleMenu(bool visible);
    void SetVisibleMenu(lWindow *menuWindow, bool visible);
    // Return true, if cursor over the menu
    bool UnderCursor();

    void RemoveFromScreen();
    void AddToScreen();
    void SetVisibleWindow(lWindow *window, bool visible);
    void SetUnvisibleAllWindows();

private:
    lGUI& operator=(const lGUI&)
    {};
    void HandleMenuEvent(StringHash eventType, VariantMap& eventData);

    bool shownMenuMain = false;
    bool shownMenuOptions = false;
};
