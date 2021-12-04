// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "PanelGUI.h"


namespace Pi
{

    class MenuContext : public PanelGUI, Singleton<MenuContext> {
    
    public:
        MenuContext();
        ~MenuContext();
    
    private:
    };

}
