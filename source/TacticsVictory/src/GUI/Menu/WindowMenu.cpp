#include "stdafx.h"
#include "MenuEvents.h"
#include "WindowMenu.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WindowMenu::WindowMenu(Context *context) : WindowRTS(context)
{

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void WindowMenu::SendEventReturn()
{
    VariantMap eventData = GetEventDataMap();
    eventData[MenuEvent::P_TYPE] = MenuEvent_Return;
    SendEvent(E_MENU, eventData);
}
