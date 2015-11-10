#pragma once


class lWindow;


extern Audio            *gAudio;
extern Localization     *gLocalization;
extern UI               *gUI;
extern UIElement        *gUIRoot;
extern ResourceCache    *gCache;
extern Engine           *gEngine;
extern Input            *gInput;
extern Renderer         *gRenderer;
extern DebugRenderer    *gDebugRenderer;
extern Context          *gContext;
extern Urho3D::Scene    *gScene;
extern Urho3D::Console  *gEngineConsole;
extern DebugHud         *gDebugHud;
extern Graphics         *gGraphics;
extern FileSystem       *gFileSystem;
extern PhysicsWorld     *gPhysicsWorld;
extern Font             *gFont;
extern Time             *gTime;
extern FileSelector     *gFileSelector;
extern Urho3D::Log      *gLog;
extern Profiler         *gProfiler;

extern Camera           *gCamera;
extern lCursor           *gCursor;
extern Editor           *gEditor;
extern Settings         *gSet;
extern Level            *gLevel;
extern lTerrain          *gTerrain;

extern GUI                  *gGUI;
extern lConsole              *gConsole;
extern WindowVariables      *gWindowVars;
extern MenuMain             *gMenuMain;
extern GuiGame              *gGuiGame;
extern GuiEditor            *gGuiEditor;
extern MenuOptions          *gMenuOptions;
extern WindowConfirmExit    *gWindowConfirmExit;
extern Hint                 *gHint;
extern int                  *gCounterHint;
extern Vector<lWindow*>     gOpenedWindow;
extern PODVector<Tank*>     gTanks;
