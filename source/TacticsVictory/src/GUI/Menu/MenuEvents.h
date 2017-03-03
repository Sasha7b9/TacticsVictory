#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum
{
    MenuEvent_MenuOptionsOpen,
    MenuEvent_NewGame,
    MenuEvent_OpenEditor,
    MenuEvent_ExitInOS,
    MenuEvent_Close             // Это событие генерует окно, когда закрывается. Параметры : P_SOURCE - указатель на себя, P_DESTINATION - указатель 
                                // на предыдущее окно, или nullptr
};


URHO3D_EVENT(E_MENU, MenuEvent)
{
    URHO3D_PARAM(P_TYPE,        EventType);     // Тип события
    URHO3D_PARAM(P_SOURCE,      Source);        // Указатель на источник
    URHO3D_PARAM(P_DESTINATION, Destination);   // Указетель на целевой объект
}
