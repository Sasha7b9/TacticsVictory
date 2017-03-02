#include <stdafx.h>
#include "GlobalFunctions.h"
#include "MenuRTS.h"
#include "MenuMain.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MenuRTS::MenuRTS()
{
    gMenuMain = new MenuMain();
    SetWindowInCenterScreen(gMenuMain);
    gUIRoot->AddChild(gMenuMain);
    gMenuMain->SetVisible(true);
}
