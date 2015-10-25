#pragma once


class lWindow;


extern Localization     *gLocalization;
extern UI               *gUI;
extern UIElement        *gUIRoot;
extern ResourceCache    *gCache;
extern Engine           *gEngine;
extern Input            *gInput;
extern Renderer         *gRenderer;
extern DebugRenderer    *gDebugRenderer;
extern Context          *gContext;
extern Scene            *gScene;
extern Console          *gEngineConsole;
extern DebugHud         *gDebugHud;
extern Graphics         *gGraphics;
extern FileSystem       *gFileSystem;
extern PhysicsWorld     *gPhysicsWorld;
extern Font             *gFont;
extern Time             *gTime;
extern FileSelector     *gFileSelector;

extern lCamera          *gCamera;
extern lCursor          *gCursor;
extern lEditor          *gEditor;
extern lSettings        *gSet;
extern lLevel           *gLevel;
extern lTerrain         *gTerrain;

extern lGUI                 *gGUI;
extern lConsole             *gConsole;
extern lWindowVariables     *gWindowVars;
extern lMenuMain            *gMenuMain;
extern lGuiGame             *gGuiGame;
extern lGuiEditor           *gGuiEditor;
extern lMenuOptions         *gMenuOptions;
extern lWindowConfirmExit   *gWindowConfirmExit;
extern lHint                *gHint;
extern int                  *gCounterHint;
extern Vector<lWindow*>     gOpenedWindow;
