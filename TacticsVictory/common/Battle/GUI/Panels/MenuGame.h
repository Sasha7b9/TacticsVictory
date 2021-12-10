// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "PanelGUI.h"
#include "Battle.h"


namespace Pi
{
    class MenuGame : public PanelGUI, public Singleton<MenuGame>
    {
    public:
        MenuGame();
        ~MenuGame();

        static MenuGame *self;

        void HandleOnButtonMenu(Widget *widget, const WidgetEventData *eventData);

    private:
        TButton *btnQuit = nullptr;
        TButton *btnOptions = nullptr;
        TButton *btnReturn = nullptr;

        WidgetObserver<Battle> observerQuit {Battle::self, &Battle::HandleOnButtonQuit};
    };
}
