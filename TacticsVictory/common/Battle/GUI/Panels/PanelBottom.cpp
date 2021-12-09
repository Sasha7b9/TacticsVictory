// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include <stdafx.h>
#include "PanelBottom.h"
#include "Settings.h"
#include "GUI/Widgets/Button.h"
#include "PanelMap.h"
#include "PanelMain.h"
#include "MenuGame.h"


using namespace Pi;


PanelBottom *PanelBottom::self = nullptr;


PanelBottom::PanelBottom()
    : PanelGUI(SET::GUI::BOTTOM::SIZE()),
    Singleton<PanelBottom>(PanelBottom::self),
    observerPanelMainHide((new PanelMain(), PanelMain::self), &PanelMain::HandleHideShow),
    observerPanelMapHide((new PanelMap(), PanelMap::self), &PanelMap::HandleHideShow),
    observerButtonMenu((new MenuGame(), MenuGame::self), &MenuGame::HandleOnButtonMenu)
{
    SetWidgetPosition(Point3D((float)SET::GUI::BOTTOM::X(), (float)SET::GUI::BOTTOM::Y(), 0.0f));

    btnHideMap = new TButton(TButton::Type::Normal, {10.0f, 2.0f}, "MAP");
    AppendNewSubnode(btnHideMap);

    btnHideMain = new TButton(TButton::Type::Normal, {100.0f, 2.0f}, "MAIN");
    AppendNewSubnode(btnHideMain);

    btnMenu = new TButton(TButton::Type::Normal, {SET::WINDOW::SIZE().x - 300.0f, 2.0f}, "MENU");
    AppendNewSubnode(btnMenu);

    btnHideMain->SetObserver(&observerPanelMainHide);
    btnHideMap->SetObserver(&observerPanelMapHide);
    btnMenu->SetObserver(&observerButtonMenu);
}

PanelBottom::~PanelBottom()
{
    //SAFE_DELETE(btnHideMap);
}
