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
