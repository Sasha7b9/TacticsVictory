#pragma once


enum
{
    MenuEvent_MenuOptionsOpen = 0,
    MenuEvent_NewGame = 1,
    MenuEvent_OpenEditor = 3,
    MenuEvent_ExitInOS = 4
};


EVENT(E_MENU, MenuEvent)
{
    PARAM(P_TYPE, MenuEventType);
}
