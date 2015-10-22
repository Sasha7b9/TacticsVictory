#include <stdafx.h>


#include "GuiGame.h"
#include "GUI/Elements/Button.h"
#include "GUI/Menu/PanelMap.h"
#include "GUI/Menu/PanelMain.h"
#include "GUI/Menu/PanelBottom.h"


lGuiGame::lGuiGame(Context* context) :
    UIElement(context)
{
    SetFixedSize(gSet->GetInt(TV_SCREEN_WIDTH), gSet->GetInt(TV_SCREEN_HEIGHT));

    panelMap = new lPanelMap(context);
    AddChild(panelMap);

    panelMain = new lPanelMain(context);
    AddChild(panelMain);

    panelBottom = new lPanelBottom(context);
    AddChild(panelBottom);
    panelBottom->SetPosition(0, gGraphics->GetHeight() - panelBottom->GetHeight());

    int width = gSet->GetInt(TV_PANEL_BOTTOM_BUTTON_WIDTH);
    int height = gSet->GetInt(TV_PANEL_BOTTOM_BUTTON_HEIGHT);

    int x = gSet->GetInt(TV_PANEL_MAP_WIDTH) / 2 - width / 2;
    int y = gSet->GetInt(TV_PANEL_BOTTOM_BUTTON_Y);
    buttonMap = panelBottom->AddButton("Map", x, y, width, height);
    SubscribeToEvent(buttonMap, Urho3D::E_RELEASED, HANDLER(lGuiGame, HandleButtonRelease));

    x = (int)(gSet->GetInt(TV_PANEL_MAP_WIDTH) * 1.5f) - width / 2;
    buttonMainPanel = panelBottom->AddButton("Panel", x, y, width, height);
    SubscribeToEvent(buttonMainPanel, Urho3D::E_RELEASED, HANDLER(lGuiGame, HandleButtonRelease));

    x = gSet->GetInt(TV_SCREEN_WIDTH) - 2 * width;
    buttonMenu = panelBottom->AddButton("Manu", x, y, width, height);
    SubscribeToEvent(buttonMenu, Urho3D::E_RELEASED, HANDLER(lGuiGame, HandleButtonRelease));
}

void lGuiGame::RegisterObject(Context* context)
{
    context->RegisterFactory<lGuiGame>("UI");

    COPY_BASE_ATTRIBUTES(UIElement);
}

void lGuiGame::HandleButtonRelease(StringHash, VariantMap &eventData)
{
    lButton *button = (lButton*)eventData[Urho3D::Released::P_ELEMENT].GetPtr();

    if(button == buttonMap)
    {
        panelMap->Toggle();
    }
    else if(button == buttonMainPanel)
    {
        panelMain->Toggle();
    }
}

bool lGuiGame::IntersectionX(lButton *button, int x)
{
    return x >= button->GetPosition().x_ && x <= button->GetPosition().x_ + button->GetWidth();
}

bool lGuiGame::CheckOnDeadZoneForCursorBottomScreen(int x)
{
    return IntersectionX(buttonMap, x) || IntersectionX(buttonMainPanel, x) || IntersectionX(buttonMenu, x);
}

bool lGuiGame::IsInside(IntVector2 &position)
{
    return IsVisible() && (panelBottom->IsInside(position, true) || panelMain->IsInside(position, true) || panelMap->IsInside(position, true));
}