// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include <stdafx.h>
#include "TabWidget.h"
#include "DrawingWidget.h"
#include "GUI/Panels/PanelGUI.h"
#include "Settings.h"
#include "ObjectViewportWidget.h"
#include "CheckBox.h"


using namespace Pi;


TabTitle::TabTitle(TabWidget *parent, Array<Tab*> *_tabs)
    : Widget(),
    observerSwitchTab(static_cast<TabWidgetMainPanel*>(parent), &TabWidgetMainPanel::HandleSwitchTab) {

    this->parent = parent;
    this->tabs = _tabs;

    float x = 10;
    float y = 5;
    float step = SET::GUI::BUTTON::WIDTH(TButton::Type::NameTab) - 1.0F;

    buttons.SetElementCount(_tabs->GetElementCount());

    for (int64 i = 0; i < _tabs->GetElementCount(); i++)
    {
        buttons[i] = new TButton(TButton::Type::NameTab, {x, y}, (*_tabs)[(size_t)i]->Name());
        AppendNewSubnode(buttons[(size_t)i]);
        x += step;
        buttons[(size_t)i]->SetObserver(&observerSwitchTab);
    }
}

TabTitle::~TabTitle() {

}

Tab::Tab(TabWidget *parent, pchar name) : Widget() {
    this->parent = parent;
    this->name = name;
    SetWidgetPosition(Point3D((float)SET::GUI::TAB_WIDGET::BORDER::LEFT(), (float)SET::GUI::TAB_WIDGET::BORDER::TOP(), 0.0f));
}


TabInfo::TabInfo(TabWidget *parent, pchar name)
    : Tab(parent, name) 
{
    //float delta = 3.0f;
    /*
    viewer = new ObjectViewportWidget({164, 164}, 1.0f);
    viewer->SetWidgetPosition({delta, delta, 0.0f});
    AppendNewSubnode(viewer);
    */
}


TabInfo::~TabInfo() {
    //TheGameWorld->GetRootNode()->RemoveSubnode(viewer->GetViewportCamera());
    //RemoveSubnode(viewer);
    //SAFE_DELETE(viewer);
}


TabUnits::TabUnits(TabWidget *parent, pchar name)
    : Tab(parent, name) {

    float x = 10;
    float y = 10;
    float step = SET::GUI::CHECKBOX::HEIGHT() + 3.0f;

    TButton *button = new TButton(TButton::Type::Normal, {10.0f, 10.0f}, "Units");
    AppendNewSubnode(button);

    chbxAll = new CheckBox(kTypeNormal, {x, y}, "All");
    AppendNewSubnode(chbxAll);

    chbxCivil = new CheckBox(kTypeNormal, {x, y = y + step}, "Civil");
    AppendNewSubnode(chbxCivil);

    chbxMilitary = new CheckBox(kTypeNormal, {x, y = y + step}, "Military");
    AppendNewSubnode(chbxMilitary);

    chbxGround = new CheckBox(kTypeNormal, {x, y = y + step}, "Ground");
    AppendNewSubnode(chbxGround);

    chbxWater = new CheckBox(kTypeNormal, {x, y = y + step}, "Water");
    AppendNewSubnode(chbxWater);

    chbxAir = new CheckBox(kTypeNormal, {x, y = y + step}, "Air");
    AppendNewSubnode(chbxAir);
}

TabUnits::~TabUnits() {
    SAFE_DELETE(chbxAir);
    SAFE_DELETE(chbxWater);
    SAFE_DELETE(chbxGround);
    SAFE_DELETE(chbxMilitary);
    SAFE_DELETE(chbxCivil);
    SAFE_DELETE(chbxAll);
}

TabPlatoons::TabPlatoons(TabWidget *parent, pchar name)
    : Tab(parent, name) {

    TButton *button = new TButton(TButton::Type::Normal, {15.0f, 15.0f}, "Platoons");
    AppendNewSubnode(button);
}

TabPlatoons::~TabPlatoons() {

}

TabStructures::TabStructures(TabWidget *parent, pchar name)
    : Tab(parent, name) {

    TButton *button = new TButton(TButton::Type::Normal, {20.0f, 20.0f}, "Structures");
    AppendNewSubnode(button);
}

TabStructures::~TabStructures() {

}

TabWidget::TabWidget(PanelGUI *_parent) : Widget() {
    parent = _parent;

    float parentWidth = parent->GetWidgetSize().x;
    float parentHeight = parent->GetWidgetSize().y;
    float left = static_cast<float>(SET::GUI::TAB_WIDGET::BORDER::LEFT());
    float right = static_cast<float>(SET::GUI::TAB_WIDGET::BORDER::RIGHT());
    float top = static_cast<float>(SET::GUI::TAB_WIDGET::BORDER::TOP());
    float bottom = static_cast<float>(SET::GUI::TAB_WIDGET::BORDER::BOTTOM());
    Vector2D size(parentWidth - left - right, parentHeight - top - bottom);
    mainWidget = new DrawingWidget(size);
    AppendNewSubnode(mainWidget);

    mainWidget->SetColorBrush(SET::GUI::COLOR::BORDER());
    mainWidget->DrawRectangle(0, 0, mainWidget->GetWidgetSize().x - 1, mainWidget->GetWidgetSize().y - 1);
    mainWidget->SetWidgetPosition(Point3D((float)SET::GUI::TAB_WIDGET::BORDER::LEFT(), (float)SET::GUI::TAB_WIDGET::BORDER::TOP(), 0.0f));
    mainWidget->EndScene();
}

TabWidget::~TabWidget() {
    SAFE_DELETE(mainWidget);
}

void TabWidget::AddTab(Tab * /*tab*/) {

}

TabWidgetMainPanel::TabWidgetMainPanel(PanelGUI *parent) 
    : TabWidget(parent) {

    numTabs = 4;

    TheTabInfo = new TabInfo(this, "Information");
    tabs.InsertElement(Tab_Info, TheTabInfo);
    AppendNewSubnode(TheTabInfo);
    
    TheTabUnits = new TabUnits(this, "Units");
    tabs.InsertElement(Tab_Units, TheTabUnits);
    AppendNewSubnode(TheTabUnits);

    TheTabPlatoons = new TabPlatoons(this, "Platoons");
    tabs.InsertElement(Tab_Platoons , TheTabPlatoons);
    AppendNewSubnode(TheTabPlatoons);

    TheTabStructures = new TabStructures(this, "Structures");
    tabs.InsertElement(Tab_Structures, TheTabStructures);
    AppendNewSubnode(TheTabStructures);
    
    tabTitle = new TabTitle(this, &tabs);
    AppendNewSubnode(tabTitle);

    SetActiveTab(Tab_Info);
}

TabWidgetMainPanel::~TabWidgetMainPanel() {
    for (int i = 0; i < tabs.GetElementCount(); i++) {
        SAFE_DELETE(tabs[i]);
    }

    SAFE_DELETE(tabTitle);
}

void TabWidgetMainPanel::HandleSwitchTab(Widget *widget, const WidgetEventData *) {
    TButton *button = static_cast<TButton*>(widget);

    if (button == tabTitle->buttons[Tab_Info]) {
        SetActiveTab(Tab_Info);
    } else if (button == tabTitle->buttons[Tab_Units]) {
        SetActiveTab(Tab_Units);
    } else if (button == tabTitle->buttons[Tab_Platoons]) {
        SetActiveTab(Tab_Platoons);
    } else if (button == tabTitle->buttons[Tab_Structures]) {
        SetActiveTab(Tab_Structures);
    }
}

void TabWidgetMainPanel::SetActiveTab(uint tabID) {
    for (int i = 0; i < tabs.GetElementCount(); i++) {
        RemoveSubnode(tabs[i]);
        tabTitle->buttons[i]->SetSelected(false);
    }
    AppendSubnode(tabs[tabID]);
    tabTitle->buttons[tabID]->SetSelected(true);
}