// 2021/02/15 16:12:30 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once

class  Battle;
class  Level;
class TLog;
class TScene;
class  Settings;
class  TerrainTV;

extern Battle          *TheBattle;
extern Level           *TheLevel;
extern TLog            *TheLog;
extern TScene          *TheScene;
extern Settings        *TheSet;
extern TerrainTV       *TheTerrain;

extern Vector<Connection *> connections;
