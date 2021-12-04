// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include <stdafx.h>
#include "GUI.h"
#include "Panels/PanelMap.h"
#include "Panels/PanelMain.h"
#include "Panels/PanelBottom.h"
#include "Panels/MenuMain.h"
#include "Utils/Math.h"
#include "Widgets/CursorGUI.h"
#include "Widgets/Button.h"
#include "Widgets/Console.h"
#include "Panels/MenuGame.h"
#include "Mutators/MovementMutator.h"
#include "Settings.h"


using namespace Pi;


GUI::GUI() :
    Widget(),
    Singleton<GUI>(TheGUI) 
{
    TheConsole = new Console(SET::GUI::CONSOLE::SIZE());
    TheConsole->Toggle();
    
    ThePanelBottom = new PanelBottom();

    Show();

    TheMenuMain = new MenuMain();
//    TheInterfaceMgr->AddWidget(TheMenuMain);

    TheCursor = new CursorGUI();
    TheInterfaceMgr->AddWidget(TheCursor);
}

GUI::~GUI() 
{
    TheInterfaceMgr->RemoveWidget(TheMenuMain);
    SAFE_DELETE(TheMenuMain);

    TheInterfaceMgr->RemoveWidget(TheConsole);
    SAFE_DELETE(TheConsole);
    TheInterfaceMgr->RemoveWidget(TheCursor);

    TheInterfaceMgr->RemoveWidget(ThePanelBottom);
    SAFE_DELETE(ThePanelBottom);

    TheInterfaceMgr->RemoveWidget(TheMenuGame);
    TheInterfaceMgr->RemoveWidget(ThePanelMain);
    TheInterfaceMgr->RemoveWidget(ThePanelMap);

    SAFE_DELETE(ThePanelMap);
    SAFE_DELETE(ThePanelMain);
    SAFE_DELETE(TheMenuGame);
}

void GUI::Hide()
{
    TheInterfaceMgr->RemoveWidget(TheConsole);
    TheInterfaceMgr->RemoveWidget(ThePanelMap);
    TheInterfaceMgr->RemoveWidget(ThePanelMain);
    TheInterfaceMgr->RemoveWidget(ThePanelBottom);
    TheInterfaceMgr->RemoveWidget(TheMenuGame);
}

void GUI::Show()
{
    TheInterfaceMgr->AddWidget(TheConsole);
    TheInterfaceMgr->AddWidget(ThePanelMap);
    TheInterfaceMgr->AddWidget(ThePanelMain);
    TheInterfaceMgr->AddWidget(ThePanelBottom);
    TheInterfaceMgr->AddWidget(TheMenuGame);
}




