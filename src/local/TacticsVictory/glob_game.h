// 2021/02/15 16:12:30 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once


class TCamera;
class TConsole;
class TCursor;
class  Editor;
class  GUI;
class  GuiEditor;
class  GuiGame;
class  Hint;
class  Level;
class CLog;
class  MenuConfirmExit;
class  MenuGame;
class TMenu;
class  Mouse;
class  PathIndicator;
class CScene;
class  Settings;
class  TacticsVictory;
class TTerrain;
class  WindowTarget;
class  WindowVariables;
class TWindow;

extern TCamera          *TheCamera;
extern TConsole         *TheConsole;
extern TCursor          *TheCursor;
extern  Editor          *TheEditor;
extern  GUI             *TheGUI;
extern  GuiEditor       *TheGuiEditor;
extern  GuiGame         *TheGuiGame;
extern  Hint            *TheHint;
extern  Level           *TheLevel;
extern CLog             *TheLog;
extern  MenuConfirmExit *TheMenuConfirmExit;
extern  MenuGame        *TheMenuMain;
extern TMenu            *TheMenu;
extern  Mouse           *TheMouse;
extern  PathIndicator   *ThePathIndicator;
extern CScene           *TheScene;
extern  Settings        *TheSet;
extern  TacticsVictory  *TheTacticsVictory;
extern TTerrain         *TheTerrain;
extern  WindowTarget    *TheWindowTarget;             // В этом окне можно посмотреть, что видит юнит
extern  WindowVariables *TheWindowVars;

extern Vector<TWindow *> TheOpenedWindow;
