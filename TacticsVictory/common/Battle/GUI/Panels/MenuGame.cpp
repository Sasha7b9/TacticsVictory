#include <stdafx.h>
#include "MenuGame.h"
#include "GUI/Widgets/Button.h"
#include "Settings.h"
#include "Battle.h"


using namespace Pi;


MenuGame::MenuGame()
    : PanelGUI(SET::GUI::MENU_GAME::SIZE()),
    Singleton<MenuGame>(TheMenuGame),
    observerQuit(TheBattle, &Battle::HandleOnButtonQuit)
{

    SetWidgetPosition(Point3D((float)(SET::WINDOW::SIZE().x - 300), (float)(SET::WINDOW::SIZE().y - 64), 0.0f));

    float x = 0;
    float y = 0;

    float step = SET::GUI::BUTTON::HEIGHT(TButton::Type::Normal) - 1.0F;

    btnOptions = new TButton(TButton::Type::Normal, {x, y}, "Options");
    AppendNewSubnode(btnOptions);

    y += step;
    btnReturn = new TButton(TButton::Type::Normal, {x, y}, "Return");
    AppendNewSubnode(btnReturn);

    y += step;
    btnQuit = new TButton(TButton::Type::Normal, {x, y}, "Quit");
    AppendNewSubnode(btnQuit);

    btnQuit->SetObserver(&observerQuit);

    Hide();
}

MenuGame::~MenuGame()
{
    SAFE_DELETE(btnQuit);
    SAFE_DELETE(btnReturn);
    SAFE_DELETE(btnOptions);
}

void MenuGame::HandleOnButtonMenu(Widget * /*widget*/, const WidgetEventData * /*eventData*/)
{
    if (!Visible())
    {
        Show();
    }
    else
    {
        Hide();
    }
}