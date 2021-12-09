// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "PanelGUI.h"
#include "PanelMap.h"
#include "MenuGame.h"


namespace Pi
{
    class TButton;
    class PanelMain;


    class PanelBottom : public PanelGUI, public Singleton<PanelBottom>
    {
        friend class GUI;

    public:
        PanelBottom();
        ~PanelBottom();

        static PanelBottom *self;

    private:
        TButton *btnHideMap = nullptr;
        TButton *btnHideMain = nullptr;
        TButton *btnMenu = nullptr;

        WidgetObserver<PanelMain> observerPanelMainHide;
        WidgetObserver<PanelMap> observerPanelMapHide;
        WidgetObserver<MenuGame> observerButtonMenu;
    };
}
