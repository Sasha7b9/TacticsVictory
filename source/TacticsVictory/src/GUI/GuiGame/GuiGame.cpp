#include <stdafx.h>
#include "GuiGame.h"
#include "GUI/Controls/Button.h"
#include "GUI/Controls/Tab.h"
#include "GUI/Panels/PanelMap.h"
#include "GUI/Panels/PanelMain.h"
#include "GUI/Panels/PanelBottom.h"
#include "GUI/Windows/Console.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GuiGame::GuiGame(Context *context) :
    Object(context)
{
    CreatePanels();

    CreateTabs();

    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(GuiGame, HandleKeyDown));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GuiGame::HandleButtonRelease(StringHash, VariantMap &eventData)
{
    ButtonRTS *button = (ButtonRTS*)eventData[Released::P_ELEMENT].GetPtr();

    if(button == buttonInterface)
    {
        ToggleInterfacePanels();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool GuiGame::IsVisible()
{
    return panelMap->IsVisible();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GuiGame::SetVisible(bool visible)
{
    panelMap->SetVisible(visible);
    panelBottom->SetVisible(visible);
    panelMain->SetVisible(visible);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool GuiGame::IntersectionX(ButtonRTS *button, int x)
{
    return x >= button->GetPosition().x_ && x <= button->GetPosition().x_ + button->GetWidth();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool GuiGame::CheckOnDeadZoneForCursorBottomScreen(int x)
{
    return IntersectionX(buttonInterface, x) || IntersectionX(buttonMenu, x);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool GuiGame::IsInside(IntVector2 &position)
{
    return IsVisible() &&
        (
        panelBottom->IsInside(position, true) ||
        panelMain->IsInside(position, true) ||
        panelMap->IsInside(position, true)
        ) &&
        position.x_ > 0 &&
        position.x_ < gSet->GetInt(TV_SCREEN_WIDTH) - 1 &&
        position.y_ < gSet->GetInt(TV_SCREEN_HEIGHT) - 1;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
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

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GuiGame::HandleKeyDown(StringHash, VariantMap& eventData)
{
    if(!IsVisible() || gConsole->IsActive())
    {
        return;
    }

    int key = eventData[KeyDown::P_KEY].GetInt();

    if(KEY_IS_I)
    {
        ToggleInterfacePanels();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GuiGame::CreatePanels()
{
    panelMap = new PanelMap(gContext);
    gUIRoot->AddChild(panelMap);

    panelMain = new PanelMain(gContext);
    gUIRoot->AddChild(panelMain);

    panelBottom = new PanelBottom(gContext);
    gUIRoot->AddChild(panelBottom);

    panelBottom->SetPosition(0, gGraphics->GetHeight() - panelBottom->GetHeight());

    int width = gSet->GetInt(TV_PANEL_BOTTOM_BUTTON_WIDTH);
    int height = gSet->GetInt(TV_PANEL_BOTTOM_BUTTON_HEIGHT);

    int x = gSet->GetInt(TV_PANEL_MAP_WIDTH) / 2 - width / 2;
    int y = gSet->GetInt(TV_PANEL_BOTTOM_BUTTON_Y);
    buttonInterface = panelBottom->AddButton("Interface", x, y, width, height);
    SubscribeToEvent(buttonInterface, E_RELEASED, URHO3D_HANDLER(GuiGame, HandleButtonRelease));

    x = gSet->GetInt(TV_SCREEN_WIDTH) - 2 * width;
    buttonMenu = panelBottom->AddButton("Menu", x, y, width, height);
    SubscribeToEvent(buttonMenu, E_RELEASED, URHO3D_HANDLER(GuiGame, HandleButtonRelease));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GuiGame::CreateTabs()
{
    CreateTabInfo();
    CreateTabUnits();
    CreateTabPlatoons();
    CreateTabBuildings();
    CreateTabDebug();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GuiGame::CreateTabInfo()
{
    SharedPtr<Tab> tabInfo(Tab::Create("Info"));
    panelMain->AddTab(tabInfo);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GuiGame::CreateTabUnits()
{
    SharedPtr<Tab> tabUnits(Tab::Create("Units"));
    panelMain->AddTab(tabUnits);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GuiGame::CreateTabPlatoons()
{
    SharedPtr<Tab> tabPlatoons(Tab::Create("Platoons"));
    panelMain->AddTab(tabPlatoons);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GuiGame::CreateTabBuildings()
{
    SharedPtr<Tab> tabBuildings(Tab::Create("Buildings"));
    panelMain->AddTab(tabBuildings);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GuiGame::CreateTabDebug()
{
    SharedPtr<Tab> tabDebug(Tab::Create("Debug"));
    panelMain->AddTab(tabDebug);
}
