#pragma once


class lWindow;


extern Localization     *gLocalization;
extern UI               *gUI;
extern UIElement        *gUIRoot;
extern ResourceCache    *gCache;
extern UEngine          *gEngine;
extern UInput           *gInput;
extern Renderer         *gRenderer;
extern DebugRenderer    *gDebugRenderer;
extern Context          *gContext;
extern Urho3D::Scene    *gScene;
extern UConsole         *gEngineConsole;
extern UDebugHud        *gDebugHud;
extern UGraphics        *gGraphics;
extern FileSystem       *gFileSystem;
extern PhysicsWorld     *gPhysicsWorld;
extern Font             *gFont;
extern Time             *gTime;
extern FileSelector     *gFileSelector;
extern ULog             *gLog;

extern Camera           *gCamera;
extern Cursor           *gCursor;
extern Editor           *gEditor;
extern Settings         *gSet;
extern Level            *gLevel;
extern Terrain          *gTerrain;

extern GUI                  *gGUI;
extern Console              *gConsole;
extern WindowVariables      *gWindowVars;
extern MenuMain             *gMenuMain;
extern GuiGame              *gGuiGame;
extern GuiEditor            *gGuiEditor;
extern MenuOptions          *gMenuOptions;
extern WindowConfirmExit    *gWindowConfirmExit;
extern Hint                 *gHint;
extern int                  *gCounterHint;
extern Vector<lWindow*>     gOpenedWindow;
