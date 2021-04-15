// 2021/02/15 16:12:30 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Battler.h"
#include "FileSystem/ConfigurationFile_.h"
#include "GUI/Cursor_.h"
#include "GUI/Controls/Hint_.h"
#include "GUI/GuiEditor/GuiEditor.h"
#include "GUI/GuiGame/GuiGame.h"
#include "GUI/GuiGame/WindowTarget.h"
#include "GUI/Menu/PageGame.h"
#include "GUI/Windows/Console_.h"
#include "GUI/Windows/WindowVariables_.h"
#include "Scene/Cameras/Camera_.h"

class Menus;

extern ConfigurationFile  TheSettings;

extern Battler           *TheBattler;
extern CameraT           *TheCamera;
extern ConsoleT          *TheConsole;
extern CursorT           *TheCursor;
extern Editor            *TheEditor;
extern GUI               *TheGUI;
extern GuiEditor         *TheGuiEditor;
extern GuiGame           *TheGuiGame;
extern Hint              *TheHint;
extern Menus             *TheMenu;
extern Mouse             *TheMouse;
extern PageGame          *ThePageGame;
extern PathIndicator     *ThePathIndicator;
extern SceneC            *TheScene;
extern ServerC           *TheServer;
extern TerrainT          *TheTerrain;
extern WindowTarget      *TheWindowTarget;             // В этом окне можно посмотреть, что видит юнит
extern WindowVariables   *TheWindowVars;

extern Vector<Control *> TheOpenedWindow;
