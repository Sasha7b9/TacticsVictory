#include <stdafx.h>


tvMenuEditor::tvMenuEditor(Context* context) :
    UIElement(context)
{
    SetFixedSize(gSet->GetInt(TV_SCREEN_WIDTH), gSet->GetInt(TV_SCREEN_HEIGHT));

    panelMap = CreateChild<tvPanelMap>();
    AddChild(panelMap);

    panelMain = CreateChild<tvPanelMain>();
    AddChild(panelMain);

    // Tab "File"
    SharedPtr<tvTab> tabFile(tvTab::Create(panelMain, "File"));

    SharedPtr<tvButton> btnFileOpen = tabFile->AddButton("Open", 10, 10);

    panelMain->AddTab(tabFile);

    // Tab "Edit"
    SharedPtr<tvTab> tabEdit(tvTab::Create(panelMain, "Edit"));

    SharedPtr<tvButton> btnFileSave = tabEdit->AddButton("Save", 200, 10);

    panelMain->AddTab(tabEdit);

    panelBottom = CreateChild<tvPanelBottom>();
    panelBottom->SetPosition(0, gSet->GetInt(TV_SCREEN_HEIGHT) - gSet->GetInt(TV_PANEL_BOTTOM_HEIGHT));
    AddChild(panelBottom);

    int width = gSet->GetInt(TV_PANEL_BOTTOM_BUTTON_WIDTH);
    int height = gSet->GetInt(TV_PANEL_BOTTOM_BUTTON_HEIGHT);

    int x = gSet->GetInt(TV_PANEL_MAP_WIDTH) / 2 - width / 2;
    int y = gSet->GetInt(TV_PANEL_BOTTOM_BUTTON_Y);

    buttonMap = panelBottom->AddButton("Map", x, y, width, height);
    SubscribeToEvent(buttonMap, E_RELEASED, HANDLER(tvMenuEditor, HandleButtonRelease));

    x = (int)(gSet->GetInt(TV_PANEL_MAP_WIDTH) * 1.5f) - width / 2;
    buttonMainPanel = panelBottom->AddButton("Panel", x, y, width, height);
    SubscribeToEvent(buttonMainPanel, E_RELEASED, HANDLER(tvMenuEditor, HandleButtonRelease));

    x = gSet->GetInt(TV_SCREEN_WIDTH) - 2 * width;
    buttonMenu = panelBottom->AddButton("Menu", x, y, width, height);
    SubscribeToEvent(buttonMenu, E_RELEASED, HANDLER(tvMenuEditor, HandleButtonRelease));

    RemoveChild(panelBottom);
    AddChild(panelBottom);
}

void tvMenuEditor::RegisterObject(Context *context)
{
    context->RegisterFactory<tvMenuEditor>("UI");

    COPY_BASE_ATTRIBUTES(UIElement);
}

void tvMenuEditor::HandleButtonRelease(StringHash, VariantMap &eventData)
{
    tvButton *button = (tvButton*)eventData[Urho3D::Released::P_ELEMENT].GetPtr();

    if (button == buttonMap)
    {
        panelMap->Toggle();
    }
    else if (button == buttonMainPanel)
    {
        panelMain->Toggle();
    }
}

bool tvMenuEditor::IntersectionX(tvButton *button, int x)
{
    return x >= button->GetPosition().x_ && x <= button->GetPosition().x_ + button->GetWidth();
}

bool tvMenuEditor::CheckOnDeadZoneForCursorBottomScreen(int x)
{
    return IntersectionX(buttonMap, x) || IntersectionX(buttonMainPanel, x) || IntersectionX(buttonMenu, x);
}