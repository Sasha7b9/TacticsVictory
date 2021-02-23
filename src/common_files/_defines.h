// 2021/02/23 22:42:59 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once

#define JSON_MODEL_TANK     "Models/Tank.json"

#define VAR_NODE_IS_UNIT    "isUnit"

#define NAME_NODE_TANK      "Tank"
#define NAME_NODE_TERRAIN   "Terrain"
#define NAME_NODE_TILE_PATH "TilePath"

#define RESOURCES_DIR       "TVData"

#define SERVER_ADDRESS      "127.0.0.1"
#define SERVER_PORT         1000

typedef unsigned char      uchar;
typedef short unsigned     uint16;
typedef unsigned int       uint;
typedef unsigned long long uint64;
typedef const char        *pchar;

typedef float(*pFuncFV)();
typedef void(*pFuncVF)(float);
