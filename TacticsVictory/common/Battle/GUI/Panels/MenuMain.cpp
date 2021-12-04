#include "stdafx.h"
#include "MenuMain.h"
#include "Settings.h"
#include "Battle.h"


using namespace Pi;


static float CalculateX()
{
    return (SET::GUI::MENU_MAIN::SIZE().x - SET::GUI::BUTTON::WIDTH(TButton::Type::Normal)) / 2.0f;
}

static float CalculateY(int numButton)
{
    return 75.0f + static_cast<float>(numButton) * 25.0f;
}

MenuMain::MenuMain()
    : PanelGUI(SET::GUI::MENU_MAIN::SIZE()),
    Singleton<MenuMain>(TheMenuMain),
    observerQuit(TheBattle, &Battle::HandleOnButtonQuit)
{
    SetWidgetPosition(Point3D((SET::WINDOW::SIZE().x - SET::GUI::MENU_MAIN::SIZE().x) / 2.0f, (SET::WINDOW::SIZE().y - SET::GUI::MENU_MAIN::SIZE().y) / 2.0f, 0.0f));

    btnLanguage = new TButton(TButton::Type::Normal, {CalculateX(), CalculateY(0)}, "Language");
    AppendNewSubnode(btnLanguage);

    btnGameTankist = new TButton(TButton::Type::Normal, {CalculateX(), CalculateY(1)}, "Tankist");
    AppendNewSubnode(btnGameTankist);

    btnGameTacticsVictory = new TButton(TButton::Type::Normal, {CalculateX(), CalculateY(2)}, "Tactics Victory");
    AppendNewSubnode(btnGameTacticsVictory);

    btnEditor = new TButton(TButton::Type::Normal, {CalculateX(), CalculateY(3)}, "Editor");
    AppendNewSubnode(btnEditor);

    btnSettings = new TButton(TButton::Type::Normal, {CalculateX(), CalculateY(4)}, "Settings");
    AppendNewSubnode(btnSettings);

    btnAbout = new TButton(TButton::Type::Normal, {CalculateX(), CalculateY(5)}, "About");
    AppendNewSubnode(btnAbout);

    btnDonate = new TButton(TButton::Type::Normal, {CalculateX(), CalculateY(6)}, "Donate");
    AppendNewSubnode(btnDonate);

    btnExit = new TButton(TButton::Type::Normal, {CalculateX(), CalculateY(7)}, "Exit");
    AppendNewSubnode(btnExit);

    btnExit->SetObserver(&observerQuit);
}

MenuMain::~MenuMain()
{

}