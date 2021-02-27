// 2021/02/15 16:12:30 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once

class Battle;
class Level;
class LogT;
class SceneT;
class Settings;
class TerrainT;

extern Battle     *TheBattle;
extern Level      *TheLevel;
extern LogT       *TheLog;
extern SceneT     *TheScene;
extern Settings   *TheSet;
extern TerrainT   *TheTerrain;

extern Vector<Connection *> connections;
