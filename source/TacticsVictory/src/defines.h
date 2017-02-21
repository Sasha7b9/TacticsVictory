#pragma once 


typedef float(*pFuncFV)();
typedef void(*pFuncVF)(float);
typedef void(*pFuncVI)(int);

typedef unsigned char   uint8;
typedef long int        int64;
typedef short unsigned  uint16;
typedef unsigned int    uint;
typedef unsigned short  ushort;
typedef unsigned char   uchar;


#define WIDTH_WINDOW_TARGET 500
#define HEIGHT_WINDOW_TARGET 300

#define SAFE_DELETE(x) if(x) delete x; x = nullptr;
#define SAFE_DELETE_ARRAY(x) if(x) delete[]x; x = nullptr;

#define NODE_TERRAIN        "lTerrain"
#define NODE_TANK           "Tank"
#define NODE_MILITARY_PLANT "Military Plant"
#define NODE_TILE_PATH      "TilePath"
#define NODE_TRIGGER        "Trigger"
#define RESOURCES_DIR       "TVData/"

#define VIEW_MASK_FOR_MISSILE   1
#define VIEW_MASK_FOR_EFFECTS   2

#define PROFILER_FUNC_ENTER     gProfiler->BeginBlock(__FUNCTION__);
#define PROFILER_FUNC_LEAVE     gProfiler->EndBlock();

#define CONSTRUCTORS(name, parent)        name(name const&) : parent(nullptr) {}; name operator=(name const&) {};
