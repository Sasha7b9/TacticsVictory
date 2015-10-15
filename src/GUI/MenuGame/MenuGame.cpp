#include <stdafx.h>


tvMenuGame::tvMenuGame(Context* context) :
    UIElement(context)
{
    SetFixedSize(gSet->GetInt(TV_SCREEN_WIDTH), gSet->GetInt(TV_SCREEN_HEIGHT));

    panelMap = new tvPanelMap(context);
    AddChild(panelMap);

    panelMain = new tvPanelMain(context);
    AddChild(panelMain);

    panelBottom = new tvPanelBottom(context);
    AddChild(panelBottom);
    panelBottom->SetPosition(0, gGraphics->GetHeight() - panelBottom->GetHeight());

    int width = gSet->GetInt(TV_PANEL_BOTTOM_BUTTON_WIDTH);
    int height = gSet->GetInt(TV_PANEL_BOTTOM_BUTTON_HEIGHT);

    int x = gSet->GetInt(TV_PANEL_MAP_WIDTH) / 2 - width / 2;
    int y = gSet->GetInt(TV_PANEL_BOTTOM_BUTTON_Y);
    buttonMap = panelBottom->AddButton("Map", x, y, width, height);
    SubscribeToEvent(buttonMap, E_RELEASED, HANDLER(tvMenuGame, HandleButtonRelease));

    x = (int)(gSet->GetInt(TV_PANEL_MAP_WIDTH) * 1.5f) - width / 2;
    buttonMainPanel = panelBottom->AddButton("Panel", x, y, width, height);
    SubscribeToEvent(buttonMainPanel, E_RELEASED, HANDLER(tvMenuGame, HandleButtonRelease));

    x = gSet->GetInt(TV_SCREEN_WIDTH) - 2 * width;
    buttonMenu = panelBottom->AddButton("Manu", x, y, width, height);
    SubscribeToEvent(buttonMenu, E_RELEASED, HANDLER(tvMenuGame, HandleButtonRelease));
}

void tvMenuGame::RegisterObject(Context* context)
{
    context->RegisterFactory<tvMenuGame>("UI");

    COPY_BASE_ATTRIBUTES(UIElement);
}

void tvMenuGame::HandleButtonRelease(StringHash, VariantMap &eventData)
{
    tvButton *button = (tvButton*)eventData[Urho3D::Released::P_ELEMENT].GetPtr();

    if(button == buttonMap)
    {
        panelMap->Toggle();
    }
    else if(button == buttonMainPanel)
    {
        panelMain->Toggle();
    }
}

bool tvMenuGame::IntersectionX(tvButton *button, int x)
{
    return x >= button->GetPosition().x_ && x <= button->GetPosition().x_ + button->GetWidth();
}

bool tvMenuGame::CheckOnDeadZoneForCursorBottomScreen(int x)
{
    return IntersectionX(buttonMap, x) || IntersectionX(buttonMainPanel, x) || IntersectionX(buttonMenu, x);
}