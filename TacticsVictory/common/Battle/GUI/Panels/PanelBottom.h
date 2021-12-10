// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Panels/PanelGUI.h"
#include "GUI/Panels/PanelMap.h"
#include "GUI/Panels/MenuGame.h"
#include "GUI/Panels/PanelMain.h"


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

        WidgetObserver<PanelMain> observerPanelMainHide {(new PanelMain(), PanelMain::self), &PanelMain::HandleHideShow};
        WidgetObserver<PanelMap> observerPanelMapHide {(new PanelMap(), PanelMap::self), &PanelMap::HandleHideShow};
        WidgetObserver<MenuGame> observerButtonMenu {(new MenuGame(), MenuGame::self), &MenuGame::HandleOnButtonMenu};
    };
}
