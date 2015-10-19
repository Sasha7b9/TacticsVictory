#pragma once


EVENT(E_MENU, MenuEvent)
{
    PARAM(P_TYPE, MenuEventType);
}


enum
{
    MenuEvent_MenuOptionsOpen = 0,
    MenuEvent_NewGame = 1,
    MenuEvent_OpenEditor = 3,
    MenuEvent_ExitInOS = 4
};


class tvGUI : public Object
{
    OBJECT(tvGUI);

public:
    tvGUI();

    void Create();
    bool GheckOnDeadZoneForCursorBottomScreen(int x);
    bool MenuIsVisible();
    void SetVisibleMenu(bool visible);
    void SetVisibleMenu(tvWindow *menuWindow, bool visible);

private:
    tvGUI& operator=(const tvGUI&)
    {};
    void HandleGuiEvent(StringHash eventType, VariantMap& eventData);
};
