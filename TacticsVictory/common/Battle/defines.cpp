#include <stdafx.h>
#include "Battle.h"
#include "Scene/Cameras/CameraRTS.h"


using namespace Pi;

namespace Pi
{

    class Game;
    class GameWorld;
    class GUI;
    class CursorGUI;
    
    class PanelMap;
    class PanelMain;
    class PanelBottom;
    class PanelPlant;
    
    class MenuMain;
    class MenuContext;
    class MenuPause;
    class MenuGame;
    
    class TabWidgetMainPanel;
    class TabInfo;
    class TabUnits;
    class TabPlatoons;
    class TabStructures;
    
    class SoundPlayer;
    class Console;
    class Mouse;


    Battle     *TheBattle = nullptr;
    GUI        *TheGUI = nullptr;
    CursorGUI  *TheCursor = nullptr;
    CameraRTS  *TheCamera = nullptr;
    Mouse      *TheMouse = nullptr;
    GameWorld  *TheGameWorld = nullptr;
    
    TabWidgetMainPanel  *TheTabWidgetMainPanel = nullptr;
    TabInfo             *TheTabInfo = nullptr;
    TabUnits            *TheTabUnits = nullptr;
    TabPlatoons         *TheTabPlatoons = nullptr;
    TabStructures       *TheTabStructures = nullptr;
    
    PanelMap    *ThePanelMap = nullptr;
    PanelMain   *ThePanelMain = nullptr;
    PanelBottom *ThePanelBottom = nullptr;
    PanelPlant  *ThePanelPlant = nullptr;
    MenuMain    *TheMenuMain = nullptr;
    MenuContext *TheMenuContext = nullptr;
    MenuPause   *TheMenuPause = nullptr;
    MenuGame    *TheMenuGame = nullptr;
    
    SoundPlayer *TheSoundPlayer = nullptr;
    Console     *TheConsole = nullptr;

}
