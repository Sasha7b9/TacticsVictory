// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "PanelGUI.h"


namespace Pi
{

    class PanelMain : public PanelGUI, public Singleton<PanelMain>
    {
    public:
        PanelMain();
        ~PanelMain();
    
        void HandleHideShow(Widget *widget, const WidgetEventData *eventData);
    
    private:
    };
    
    extern PanelMain *ThePanelMain;

}
