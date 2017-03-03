#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum
{
    MenuEvent_MenuOptionsOpen,
    MenuEvent_NewGame,
    MenuEvent_OpenEditor,
    MenuEvent_ExitInOS,
    MenuEvent_Return            // Это событие генерует окно, когда закрывается для перехода предудущий уровень
};


URHO3D_EVENT(E_MENU, MenuEvent)
{
    URHO3D_PARAM(P_TYPE, MenuEventType);
}
