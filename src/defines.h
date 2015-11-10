#pragma once


typedef float(*pFuncFV)();
typedef void(*pFuncVF)(float);
typedef void(*pFuncVI)(int);

typedef long int int64;
typedef short unsigned uint16;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

#define SAFE_DELETE(x) if(x) delete x; x = nullptr;
#define SAFE_DELETE_ARRAY(x) if(x) delete[]x; x = nullptr;

#define NODE_TERRAIN    "lTerrain"
#define NODE_TANK       "Tank"
#define NODE_TILE_PATH  "TilePath"
#define NODE_TRIGGER    "Trigger"

