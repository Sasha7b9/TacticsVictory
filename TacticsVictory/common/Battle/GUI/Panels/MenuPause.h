#pragma once
#include "PanelGUI.h"


namespace Pi
{

    class MenuPause : public PanelGUI, Singleton<MenuPause> {
    
    public:
        MenuPause();
        ~MenuPause();
    
    private:
    };

}
