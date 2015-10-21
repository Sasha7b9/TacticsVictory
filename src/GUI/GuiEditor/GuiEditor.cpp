#include <stdafx.h>


#include "GuiEditor.h"
#include "GUI/Elements/Tab.h"
#include "GUI/Elements/Button.h"
#include "GUI/Elements/ButtonToggled.h"
#include "GUI/Menu/PanelMap.h"
#include "GUI/Menu/PanelMain.h"
#include "GUI/Menu/PanelBottom.h"


lGuiEditor::lGuiEditor(Context* context) :
    UIElement(context)
{
    SetFixedSize(gSet->GetInt(TV_SCREEN_WIDTH), gSet->GetInt(TV_SCREEN_HEIGHT));

    panelMap = new lPanelMap(gContext);
    AddChild(panelMap);

    panelMain = new lPanelMain(gContext);
    AddChild(panelMain);

    // Tab "File"
    SharedPtr<lTab> tabFile(lTab::Create("File"));
    SharedPtr<lButton> btnFileOpen = tabFile->AddButton("Open", 10, 10);
    panelMain->AddTab(tabFile);

    // Tab "Edit"
    SharedPtr<lTab> tabEdit(lTab::Create("Edit"));
    SharedPtr<lButton> btnFileSave = tabEdit->AddButton("Save", 200, 10);
    panelMain->AddTab(tabEdit);

    panelBottom = new lPanelBottom(gContext);
    panelBottom->SetPosition(0, gSet->GetInt(TV_SCREEN_HEIGHT) - gSet->GetInt(TV_PANEL_BOTTOM_HEIGHT));

    int width = gSet->GetInt(TV_PANEL_BOTTOM_BUTTON_WIDTH);
    int height = gSet->GetInt(TV_PANEL_BOTTOM_BUTTON_HEIGHT);

    int x = gSet->GetInt(TV_PANEL_MAP_WIDTH) / 2 - width / 2;
    int y = gSet->GetInt(TV_PANEL_BOTTOM_BUTTON_Y);

    buttonMap = panelBottom->AddButton("Map", x, y, width, height);
    SubscribeToEvent(buttonMap, E_RELEASED, HANDLER(lGuiEditor, HandleButtonRelease));

    x = (int)(gSet->GetInt(TV_PANEL_MAP_WIDTH) * 1.5f) - width / 2;
    buttonMainPanel = panelBottom->AddButton("Panel", x, y, width, height);
    SubscribeToEvent(buttonMainPanel, E_RELEASED, HANDLER(lGuiEditor, HandleButtonRelease));

    x = gSet->GetInt(TV_SCREEN_WIDTH) - 2 * width;
    buttonMenu = panelBottom->AddButton("Menu", x, y, width, height);
    SubscribeToEvent(buttonMenu, E_RELEASED, HANDLER(lGuiEditor, HandleButtonRelease));

    AddChild(panelBottom);
    panelBottom->BringToFront();
}

void lGuiEditor::RegisterObject(Context *context)
{
    context->RegisterFactory<lGuiEditor>("UI");

    COPY_BASE_ATTRIBUTES(UIElement);
}

void lGuiEditor::HandleButtonRelease(StringHash, VariantMap &eventData)
{
    lButton *button = (lButton*)eventData[Urho3D::Released::P_ELEMENT].GetPtr();

    if (button == buttonMap)
    {
        panelMap->Toggle();
    }
    else if (button == buttonMainPanel)
    {
        panelMain->Toggle();
    }
}

bool lGuiEditor::IntersectionX(lButton *button, int x)
{
    return x >= button->GetPosition().x_ && x <= button->GetPosition().x_ + button->GetWidth();
}

bool lGuiEditor::CheckOnDeadZoneForCursorBottomScreen(int x)
{
    return IntersectionX(buttonMap, x) || IntersectionX(buttonMainPanel, x) || IntersectionX(buttonMenu, x);
}

bool lGuiEditor::IsInside(IntVector2 &position)
{
    return IsVisible() && (panelBottom->IsInside(position, true) || panelMain->IsInside(position, true) || panelMap->IsInside(position, true)) && 
        position.x_ > 0 && 
        position.x_ < gSet->GetInt(TV_SCREEN_WIDTH) - 1 &&
        position.y_ < gSet->GetInt(TV_SCREEN_HEIGHT) - 1;
}

void lGuiEditor::TogglePanelMain()
{
    panelMain->Toggle();
}

void lGuiEditor::TogglePanelMap()
{
    panelMap->Toggle();
}