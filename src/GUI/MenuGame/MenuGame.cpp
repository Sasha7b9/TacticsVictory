#include <stdafx.h>


#include "MenuGame.h"
#include "GUI/Elements/Button.h"
#include "GUI/Menu/PanelMap.h"
#include "GUI/Menu/PanelMain.h"
#include "GUI/Menu/PanelBottom.h"


vMenuGame::vMenuGame(Context* context) :
    UIElement(context)
{
    SetFixedSize(gSet->GetInt(TV_SCREEN_WIDTH), gSet->GetInt(TV_SCREEN_HEIGHT));

    panelMap = new vPanelMap(context);
    AddChild(panelMap);

    panelMain = new vPanelMain(context);
    AddChild(panelMain);

    panelBottom = new vPanelBottom(context);
    AddChild(panelBottom);
    panelBottom->SetPosition(0, gGraphics->GetHeight() - panelBottom->GetHeight());

    int width = gSet->GetInt(TV_PANEL_BOTTOM_BUTTON_WIDTH);
    int height = gSet->GetInt(TV_PANEL_BOTTOM_BUTTON_HEIGHT);

    int x = gSet->GetInt(TV_PANEL_MAP_WIDTH) / 2 - width / 2;
    int y = gSet->GetInt(TV_PANEL_BOTTOM_BUTTON_Y);
    buttonMap = panelBottom->AddButton("Map", x, y, width, height);
    SubscribeToEvent(buttonMap, E_RELEASED, HANDLER(vMenuGame, HandleButtonRelease));

    x = (int)(gSet->GetInt(TV_PANEL_MAP_WIDTH) * 1.5f) - width / 2;
    buttonMainPanel = panelBottom->AddButton("Panel", x, y, width, height);
    SubscribeToEvent(buttonMainPanel, E_RELEASED, HANDLER(vMenuGame, HandleButtonRelease));

    x = gSet->GetInt(TV_SCREEN_WIDTH) - 2 * width;
    buttonMenu = panelBottom->AddButton("Manu", x, y, width, height);
    SubscribeToEvent(buttonMenu, E_RELEASED, HANDLER(vMenuGame, HandleButtonRelease));
}

void vMenuGame::RegisterObject(Context* context)
{
    context->RegisterFactory<vMenuGame>("UI");

    COPY_BASE_ATTRIBUTES(UIElement);
}

void vMenuGame::HandleButtonRelease(StringHash, VariantMap &eventData)
{
    vButton *button = (vButton*)eventData[Urho3D::Released::P_ELEMENT].GetPtr();

    if(button == buttonMap)
    {
        panelMap->Toggle();
    }
    else if(button == buttonMainPanel)
    {
        panelMain->Toggle();
    }
}

bool vMenuGame::IntersectionX(vButton *button, int x)
{
    return x >= button->GetPosition().x_ && x <= button->GetPosition().x_ + button->GetWidth();
}

bool vMenuGame::CheckOnDeadZoneForCursorBottomScreen(int x)
{
    return IntersectionX(buttonMap, x) || IntersectionX(buttonMainPanel, x) || IntersectionX(buttonMenu, x);
}