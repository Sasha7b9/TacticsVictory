// 2021/02/15 16:12:30 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once

class  Battle;
class  Level;
class TLog;
class SceneT;
class  Settings;
class  TTerrain;

extern Battle          *TheBattle;
extern Level           *TheLevel;
extern TLog            *TheLog;
extern SceneT          *TheScene;
extern Settings        *TheSet;
extern TTerrain       *TheTerrain;

extern Vector<Connection *> connections;
