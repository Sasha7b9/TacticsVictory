#include <stdafx.h>


#include "MenuEditor.h"
#include "GUI/Elements/Tab.h"
#include "GUI/Elements/Button.h"
#include "GUI/Elements/ButtonToggled.h"
#include "GUI/Menu/PanelMap.h"
#include "GUI/Menu/PanelMain.h"
#include "GUI/Menu/PanelBottom.h"


vMenuEditor::vMenuEditor(Context* context) :
    UIElement(context)
{
    SetFixedSize(gSet->GetInt(TV_SCREEN_WIDTH), gSet->GetInt(TV_SCREEN_HEIGHT));

    panelMap = CreateChild<vPanelMap>();
    AddChild(panelMap);

    panelMain = CreateChild<vPanelMain>();
    AddChild(panelMain);

    // Tab "File"
    SharedPtr<vTab> tabFile(vTab::Create(panelMain, "File"));

    SharedPtr<vButton> btnFileOpen = tabFile->AddButton("Open", 10, 10);

    panelMain->AddTab(tabFile);

    // Tab "Edit"
    SharedPtr<vTab> tabEdit(vTab::Create(panelMain, "Edit"));

    SharedPtr<vButton> btnFileSave = tabEdit->AddButton("Save", 200, 10);

    panelMain->AddTab(tabEdit);

    panelBottom = CreateChild<vPanelBottom>();
    panelBottom->SetPosition(0, gSet->GetInt(TV_SCREEN_HEIGHT) - gSet->GetInt(TV_PANEL_BOTTOM_HEIGHT));
    AddChild(panelBottom);

    int width = gSet->GetInt(TV_PANEL_BOTTOM_BUTTON_WIDTH);
    int height = gSet->GetInt(TV_PANEL_BOTTOM_BUTTON_HEIGHT);

    int x = gSet->GetInt(TV_PANEL_MAP_WIDTH) / 2 - width / 2;
    int y = gSet->GetInt(TV_PANEL_BOTTOM_BUTTON_Y);

    buttonMap = panelBottom->AddButton("Map", x, y, width, height);
    SubscribeToEvent(buttonMap, E_RELEASED, HANDLER(vMenuEditor, HandleButtonRelease));

    x = (int)(gSet->GetInt(TV_PANEL_MAP_WIDTH) * 1.5f) - width / 2;
    buttonMainPanel = panelBottom->AddButton("Panel", x, y, width, height);
    SubscribeToEvent(buttonMainPanel, E_RELEASED, HANDLER(vMenuEditor, HandleButtonRelease));

    x = gSet->GetInt(TV_SCREEN_WIDTH) - 2 * width;
    buttonMenu = panelBottom->AddButton("Menu", x, y, width, height);
    SubscribeToEvent(buttonMenu, E_RELEASED, HANDLER(vMenuEditor, HandleButtonRelease));

    RemoveChild(panelBottom);
    AddChild(panelBottom);
}

void vMenuEditor::RegisterObject(Context *context)
{
    context->RegisterFactory<vMenuEditor>("UI");

    COPY_BASE_ATTRIBUTES(UIElement);
}

void vMenuEditor::HandleButtonRelease(StringHash, VariantMap &eventData)
{
    vButton *button = (vButton*)eventData[Urho3D::Released::P_ELEMENT].GetPtr();

    if (button == buttonMap)
    {
        panelMap->Toggle();
    }
    else if (button == buttonMainPanel)
    {
        panelMain->Toggle();
    }
}

bool vMenuEditor::IntersectionX(vButton *button, int x)
{
    return x >= button->GetPosition().x_ && x <= button->GetPosition().x_ + button->GetWidth();
}

bool vMenuEditor::CheckOnDeadZoneForCursorBottomScreen(int x)
{
    return IntersectionX(buttonMap, x) || IntersectionX(buttonMainPanel, x) || IntersectionX(buttonMenu, x);
}