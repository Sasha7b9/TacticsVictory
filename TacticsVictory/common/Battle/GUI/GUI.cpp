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


namespace Pi
{
    GUI *GUI::self = nullptr;
}


GUI::GUI() :
    Widget(),
    Singleton<GUI>(self)
{
    new Console(SET::GUI::CONSOLE::SIZE());
    Console::self->Toggle();
    
    new PanelBottom();

    Show();

    new MenuMain();
//    TheInterfaceMgr->AddWidget(TheMenuMain);

    new CursorGUI();
    TheInterfaceMgr->AddWidget(CursorGUI::self);
}


void GUI::Create()
{
    new GUI();
}


GUI::~GUI() 
{
    TheInterfaceMgr->RemoveWidget(MenuMain::self);
    SAFE_DELETE(MenuMain::self);

    TheInterfaceMgr->RemoveWidget(Console::self);
    SAFE_DELETE(Console::self);
    TheInterfaceMgr->RemoveWidget(CursorGUI::self);

    TheInterfaceMgr->RemoveWidget(PanelBottom::self);
    SAFE_DELETE(PanelBottom::self);

    TheInterfaceMgr->RemoveWidget(MenuGame::self);
    TheInterfaceMgr->RemoveWidget(PanelMain::self);
    TheInterfaceMgr->RemoveWidget(PanelMap::self);

    SAFE_DELETE(PanelMap::self);
    SAFE_DELETE(PanelMain::self);
    SAFE_DELETE(MenuGame::self);
}

void GUI::Hide()
{
    TheInterfaceMgr->RemoveWidget(Console::self);
    TheInterfaceMgr->RemoveWidget(PanelMap::self);
    TheInterfaceMgr->RemoveWidget(PanelMain::self);
    TheInterfaceMgr->RemoveWidget(PanelBottom::self);
    TheInterfaceMgr->RemoveWidget(MenuGame::self);
}

void GUI::Show()
{
    TheInterfaceMgr->AddWidget(Console::self);
    TheInterfaceMgr->AddWidget(PanelMap::self);
    TheInterfaceMgr->AddWidget(PanelMain::self);
    TheInterfaceMgr->AddWidget(PanelBottom::self);
    TheInterfaceMgr->AddWidget(MenuGame::self);
}




