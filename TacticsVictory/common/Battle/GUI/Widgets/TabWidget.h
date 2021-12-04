// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Panels/PanelGUI.h"


namespace Pi
{

    class PanelGUI;
    class Tab;
    class DrawingWidget;
    class CheckBox;
    class TabTitle;
    class ObjectViewportWidget;
    
    class TabWidget : public Widget
    {
    
    public:
        TabWidget(PanelGUI *parent);
        ~TabWidget();
    
        void Move() override
        {
        };
        void AddTab(Tab *tab);
    
    protected:
        TabTitle *tabTitle = nullptr;
        DrawingWidget *mainWidget = nullptr;
        int numTabs = 0;
        Array<Tab*> tabs;
    
    private:
        TabWidget();
        PanelGUI *parent = nullptr;
    };
    
    class TabWidgetMainPanel : public TabWidget
    {
        enum
        {
            Tab_Info,
            Tab_Units,
            Tab_Platoons,
            Tab_Structures
        };
    public:
        TabWidgetMainPanel(PanelGUI *parent);
        ~TabWidgetMainPanel();
    
        void HandleSwitchTab(Widget *widget, const WidgetEventData *eventData);
        void SetActiveTab(uint tabID);
    };
    
    class TabTitle : public Widget
    {
        friend class TabWidgetMainPanel;
    public:
        TabTitle(TabWidget *parent, Array<Tab*> *tabs);
        ~TabTitle();
    
        void Move() override
        {
        };
    
    private:
        TabTitle();
        TabWidget *parent;
        Array<Tab*> *tabs;
        Array<TButton*> buttons;
        WidgetObserver<TabWidgetMainPanel> observerSwitchTab;
    };
    
    class SubTab : public Widget
    {
    
    public:
        SubTab(Tab *parent);
    
    private:
        SubTab();
    };
    
    class Tab : public Widget
    {
        friend class TabTitle;
        friend class TabWidgetMainPanel;
    public:
        Tab();
        Tab(TabWidget *parent, pchar name);
        virtual ~Tab() {};
    
        void Move() override
        {
        };
        pchar Name()
        {
            return name;
        };
    
    protected:
        TabWidget *parent = nullptr;
        pchar name = nullptr;
    };
    
    class TabInfo : public Tab
    {
    public:
        TabInfo(TabWidget *parent, pchar name);
        virtual ~TabInfo() override;

    private:
        TabInfo();
    
        ObjectViewportWidget *viewer = nullptr;
    };
    
    class TabUnits : public Tab
    {
    
    public:
        TabUnits(TabWidget *parent, pchar name);
        ~TabUnits() override;
    
    private:
        TabUnits();
    
        CheckBox *chbxAll = nullptr;
        CheckBox *chbxCivil = nullptr;
        CheckBox *chbxMilitary = nullptr;
        CheckBox *chbxGround = nullptr;
        CheckBox *chbxWater = nullptr;
        CheckBox *chbxAir = nullptr;
    };
    
    class TabPlatoons : public Tab
    {
    
    public:
        TabPlatoons(TabWidget *parent, pchar name);
        ~TabPlatoons();
    
    private:
        TabPlatoons();
    };
    
    class TabStructures : public Tab
    {
    
    public:
        TabStructures(TabWidget *parent, pchar name);
        ~TabStructures();
    
    private:
        TabStructures();
    };
    
    extern TabWidgetMainPanel  *TheTabWidgetMainPanel;
    extern TabInfo             *TheTabInfo;
    extern TabUnits            *TheTabUnits;
    extern TabPlatoons         *TheTabPlatoons;
    extern TabStructures       *TheTabStructures;

}
