// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


enum
{
    ME_OPEN_PLAY,           // Открывает меню "Играть"
    ME_OPEN_OPTIONS,        // Нужно открыть меню "Опции" . P_SOURCE - меню, которое его открывает
    ME_OPEN_ABOUT_ME,
    ME_START_SERVER,
    ME_START_CLIENT,
    ME_OPEN_EDITOR,
    ME_CLOSE,               // Это событие генерует окно, когда закрывается. Параметры : P_SOURCE - указатель на себя,
                            // P_DESTINATION - указатель 
                            // на предыдущее окно, или nullptr
    ME_EXIT_IN_OS
};


URHO3D_EVENT(E_MENU, MenuEvent)
{
    URHO3D_PARAM(P_TYPE,        EventType);     // Тип события
    URHO3D_PARAM(P_SOURCE,      Source);        // Указатель на источник
    URHO3D_PARAM(P_DESTINATION, Destination);   // Указетель на целевой объект
    URHO3D_PARAM(P_PORT,        ServerPort);    // Номер порта, к которому нужно коннектиться при ME_START_SERVER
}
