// 2021/02/23 22:42:59 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once

#define JSON_MODEL_TANK     "Models/Tank.json"

#define VAR_NODE_IS_UNIT    "isUnit"

#define NAME_NODE_TANK      "Tank"
#define NAME_NODE_TERRAIN   "Terrain"
#define NAME_NODE_TILE_PATH "TilePath"

#define RESOURCES_DIR       "TVData"

#define VIEW_MASK_FOR_MISSILE   1
#define VIEW_MASK_FOR_EFFECTS   2

#define SERVER_ADDRESS      "127.0.0.1"
#define SERVER_PORT         1000

#ifdef _DEBUG
#define PROFILER_FUNC_ENTER()  TheProfiler->BeginBlock(__FUNCTION__);
#define PROFILER_FUNC_LEAVE()  TheProfiler->EndBlock();
#else
#define PROFILER_FUNC_ENTER()
#define PROFILER_FUNC_LEAVE()
#endif

typedef unsigned char      uchar;
typedef short unsigned     uint16;
typedef unsigned int       uint;
typedef unsigned long long uint64;
typedef const char        *pchar;

typedef float(*pFuncFV)();
typedef void(*pFuncVF)(float);
