// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


enum
{
    ME_OpenOptions,      // Нужно открыть меню "Опции" . P_SOURCE - меню, которое его открывает
    ME_OpenAboutMe,
    ME_StartServer,
    ME_StartClient,
    ME_OpenEditor,
    ME_Close,            // Это событие генерует окно, когда закрывается. Параметры : P_SOURCE - указатель на себя, P_DESTINATION - указатель 
                                // на предыдущее окно, или nullptr
    ME_ExitInOS
};


URHO3D_EVENT(E_MENU, MenuEvent)
{
    URHO3D_PARAM(P_TYPE,        EventType);     // Тип события
    URHO3D_PARAM(P_SOURCE,      Source);        // Указатель на источник
    URHO3D_PARAM(P_DESTINATION, Destination);   // Указетель на целевой объект
    URHO3D_PARAM(P_PORT,        ServerPort);    // Номер порта, к которому нужно коннектиться при ME_StartServer
}
