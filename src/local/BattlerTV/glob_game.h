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
class TScene;
class  Settings;
class  Battler;
class TTerrain;
class TWindow;
class  WindowTarget;
class  WindowVariables;

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
extern TScene           *TheScene;
extern  Settings        *TheSet;
extern  Battler         *TheTacticsVictory;
extern TTerrain         *TheTerrain;
extern  WindowTarget    *TheWindowTarget;             // В этом окне можно посмотреть, что видит юнит
extern  WindowVariables *TheWindowVars;

extern int *TheCounterHint;
extern Vector<TWindow *> TheOpenedWindow;
