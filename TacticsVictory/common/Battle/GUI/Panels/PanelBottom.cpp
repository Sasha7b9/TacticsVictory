﻿#include <stdafx.h>
#include "PanelBottom.h"
#include "Settings.h"
#include "GUI/Widgets/Button.h"
#include "PanelMap.h"
#include "PanelMain.h"
#include "MenuGame.h"


using namespace Pi;


PanelBottom::PanelBottom() 
    : PanelGUI(SET::GUI::BOTTOM::SIZE()),
    Singleton<PanelBottom>(ThePanelBottom),
    observerPanelMainHide((new PanelMain(), ThePanelMain), &PanelMain::HandleHideShow),
    observerPanelMapHide((new PanelMap(), ThePanelMap), &PanelMap::HandleHideShow),
    observerButtonMenu((new MenuGame(), TheMenuGame), &MenuGame::HandleOnButtonMenu) 
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
