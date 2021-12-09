// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "PanelGUI.h"


namespace Pi
{
    class Battle;
    class TButton;
    class Game;


    class MenuMain : public PanelGUI, public Singleton<MenuMain>
    {
    public:
        MenuMain();
        ~MenuMain();

        static MenuMain *self;

    private:
        TButton *btnLanguage = nullptr;

        TButton *btnGameTankist = nullptr;
        TButton *btnTankistSingle = nullptr;
        TButton *btnTankistMultiplayer = nullptr;
        TButton *btnTankistFindServer = nullptr;
        TButton *btnTankistOfficialServer = nullptr;
        TButton *btnTankistCreateServer = nullptr;

        TButton *btnGameTacticsVictory = nullptr;
        TButton *btnTVcampgain = nullptr;
        TButton *btnTVmultiplayer = nullptr;
        TButton *btnTVfindServer = nullptr;
        TButton *btnTVofficialServer = nullptr;
        TButton *btnTVcreateServer = nullptr;

        TButton *btnEditor = nullptr;

        TButton *btnSettings = nullptr;
        TButton *btnSettingsControl = nullptr;
        TButton *btnSettingsGraphics = nullptr;
        TButton *btnSettingsSound = nullptr;

        TButton *btnAbout = nullptr;

        TButton *btnDonate = nullptr;

        TButton *btnExit = nullptr;

        WidgetObserver<Battle> observerQuit;
    };
}
