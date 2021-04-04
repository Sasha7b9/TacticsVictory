// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Controls/Tab_.h"
#include "GUI/Controls/Buttons/ButtonSwitch_.h"
#include "GUI/GuiGame/GuiGame.h"
#include "GUI/Panels/PanelBottom.h"
#include "GUI/Panels/PanelMain.h"
#include "GUI/Panels/PanelMap.h"


GuiGame::GuiGame() :
    Object(TheContext)
{
    CreatePanels();

    CreateTabs();

    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(GuiGame, HandleKeyDown));
}


void GuiGame::HandleButtonRelease(StringHash, VariantMap &eventData)
{
    ButtonT *button = (ButtonT *)eventData[Released::P_ELEMENT].GetPtr();

    if(button == buttonInterface)
    {
        ToggleInterfacePanels();
    }
}


bool GuiGame::IsVisible()
{
    return panelMap->IsVisible();
}


void GuiGame::SetVisible(bool visible)
{
    panelMap->SetVisible(visible);
    panelBottom->SetVisible(visible);
    panelMain->SetVisible(visible);
}


bool GuiGame::IntersectionX(const ButtonT *button, int x)
{
    return x >= button->GetPosition().x_ && x <= button->GetPosition().x_ + button->GetWidth();
}


bool GuiGame::CheckOnDeadZoneForCursorBottomScreen(int x)
{
    return IntersectionX(buttonInterface, x) || IntersectionX(buttonMenu, x);
}


bool GuiGame::IsInside(const IntVector2 &position)
{
    return IsVisible() &&
        (
        panelBottom->IsInside(position, true) ||
        panelMain->IsInside(position, true) ||
        panelMap->IsInside(position, true)
        ) &&
        position.x_ > 0 &&
        position.x_ < TheSettings.GetInt("screen", "width") - 1 &&
        position.y_ < TheSettings.GetInt("screen", "height") - 1;
}


void GuiGame::ToggleInterfacePanels()
{
    LineTranslator2D::State stateMap = panelMap->GetTranslator()->GetState();
    LineTranslator2D::State stateMain = panelMain->GetTranslator()->GetState();

    if(stateMap == LineTranslator2D::State_PointStart && stateMain == LineTranslator2D::State_PointStart)
    {
        panelMain->Toggle();
    }
    else if(stateMap == LineTranslator2D::State_PointStart && stateMain == LineTranslator2D::State_PointFinish)
    {
        panelMap->Toggle();
    }
    else if(stateMap == LineTranslator2D::State_PointFinish && stateMain == LineTranslator2D::State_PointFinish)
    {
        panelMap->Toggle();
        panelMain->Toggle();
    }
}


void GuiGame::HandleKeyDown(StringHash, VariantMap& eventData)
{
    if(!IsVisible() || TheConsole->IsActive())
    {
        return;
    }

    int key = eventData[KeyDown::P_KEY].GetInt();

    if(KEY_IS_I)
    {
        ToggleInterfacePanels();
    }
}


void GuiGame::CreatePanels()
{
    panelMap = new PanelMap(TheContext);
    TheUIRoot->AddChild(panelMap);

    panelMain = new PanelMain(TheContext);
    TheUIRoot->AddChild(panelMain);

    panelBottom = new PanelBottom(TheContext);
    TheUIRoot->AddChild(panelBottom);

    panelBottom->SetPosition(0, TheGraphics->GetHeight() - panelBottom->GetHeight());

    int width = TheSettings.GetInt("panel_bottom", "button_width");
    int height = TheSettings.GetInt("panel_bottom", "button_height");

    int x = TheSettings.GetInt("panel_map", "width") / 2 - width / 2;
    int y = TheSettings.GetInt("panel_bottom", "y");
    buttonInterface = panelBottom->AddButton("Interface", x, y, width, height);
    SubscribeToEvent(buttonInterface, E_RELEASED, URHO3D_HANDLER(GuiGame, HandleButtonRelease));

    x = TheSettings.GetInt("screen", "width") - 2 * width;
    buttonMenu = panelBottom->AddButton("Menu", x, y, width, height);
    SubscribeToEvent(buttonMenu, E_RELEASED, URHO3D_HANDLER(GuiGame, HandleButtonRelease));
}


void GuiGame::CreateTabs()
{
    CreateTabInfo();
    CreateTabUnits();
    CreateTabPlatoons();
    CreateTabBuildings();
    CreateTabDebug();
}


void GuiGame::CreateTabInfo()
{
    SharedPtr<Tab> tabInfo(Tab::Create("Info"));
    panelMain->AddTab(tabInfo);
}


void GuiGame::CreateTabUnits()
{
    SharedPtr<Tab> tabUnits(Tab::Create("Units"));
    panelMain->AddTab(tabUnits);
}


void GuiGame::CreateTabPlatoons()
{
    SharedPtr<Tab> tabPlatoons(Tab::Create("Platoons"));
    panelMain->AddTab(tabPlatoons);
}


void GuiGame::CreateTabBuildings()
{
    SharedPtr<Tab> tabBuildings(Tab::Create("Buildings"));
    panelMain->AddTab(tabBuildings);
}


void GuiGame::CreateTabDebug()
{
    SharedPtr<Tab> tabDebug(Tab::Create("Debug"));
    panelMain->AddTab(tabDebug);
}
