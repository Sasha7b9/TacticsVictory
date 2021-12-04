#pragma once
#include "PanelGUI.h"


namespace Pi
{

    class Battle;
    
    
    class MenuGame : public PanelGUI, public Singleton<MenuGame>
    {
    public:
        MenuGame();
        ~MenuGame();
    
        void HandleOnButtonMenu(Widget *widget, const WidgetEventData *eventData);
    
    private:
        TButton *btnQuit = nullptr;
        TButton *btnOptions = nullptr;
        TButton *btnReturn = nullptr;
    
        WidgetObserver<Battle> observerQuit;
    };
    
    extern MenuGame *TheMenuGame;

}
