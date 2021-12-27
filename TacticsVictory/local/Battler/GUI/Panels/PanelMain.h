// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "PanelGUI.h"


namespace Pi
{
    class PanelMain : public PanelGUI, public Singleton<PanelMain>
    {
        friend class PanelBottom;
        friend class GUI;

    private:

        PanelMain();

        virtual ~PanelMain();

        static PanelMain *self;

        void HandleHideShow(Widget *, const WidgetEventData *);
    };
}
