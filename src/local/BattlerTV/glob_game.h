// 2021/02/15 16:12:30 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once

class  CameraT;
class  ConsoleT;
class  CursorT;
class  Editor;
class  GUI;
class  GuiEditor;
class  GuiGame;
class  Hint;
class  Level;
class  LogC;
class  MenuConfirmExit;
class  MenuGame;
class  MenuT;
class  Mouse;
class  PathIndicator;
class  SceneC;
class  Settings;
class  Battler;
class TTerrain;
class  WindowTarget;
class  WindowVariables;
class TWindow;

extern CameraT *TheCamera;
extern ConsoleT *TheConsole;
extern CursorT *TheCursor;
extern  Editor *TheEditor;
extern  GUI *TheGUI;
extern  GuiEditor *TheGuiEditor;
extern  GuiGame *TheGuiGame;
extern  Hint *TheHint;
extern  Level *TheLevel;
extern  LogC *TheLog;
extern  MenuConfirmExit *TheMenuConfirmExit;
extern  MenuGame *TheMenuMain;
extern MenuT *TheMenu;
extern  Mouse *TheMouse;
extern  PathIndicator *ThePathIndicator;
extern SceneC *TheScene;
extern  Settings *TheSet;
extern  Battler *TheBattler;
extern TTerrain *TheTerrain;
extern  WindowTarget *TheWindowTarget;             // В этом окне можно посмотреть, что видит юнит
extern  WindowVariables *TheWindowVars;

extern Vector<TWindow *> TheOpenedWindow;
