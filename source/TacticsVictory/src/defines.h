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


enum TypeCursor
{
    TypeCursor_Normal,
    TypeCursor_Selected,
    TypeCursor_Left,
    TypeCursor_Up,
    TypeCursor_Right,
    TypeCursor_Down,
    TypeCursor_TopLeft,
    TypeCursor_TopRight,
    TypeCursor_DownLeft,
    TypeCursor_DownRight,
    TypeCursor_Busy,
    TypeCursor_Size
};


#define WIDTH_WINDOW_TARGET 500
#define HEIGHT_WINDOW_TARGET 300

#define SAFE_DELETE(x) if(x) delete x; x = nullptr;
#define SAFE_DELETE_ARRAY(x) if(x) delete[]x; x = nullptr;

#define NODE_TERRAIN        "TerrainRTS"
#define NODE_TANK           "Tank"
#define NODE_MILITARY_PLANT "Military Plant"
#define NODE_TILE_PATH      "TilePath"
#define NODE_TRIGGER        "Trigger"
#define RESOURCES_DIR       "TVData/"

#define VIEW_MASK_FOR_MISSILE   1
#define VIEW_MASK_FOR_EFFECTS   2

#define PROFILER_FUNC_ENTER     gProfiler->BeginBlock(__FUNCTION__);
#define PROFILER_FUNC_LEAVE     gProfiler->EndBlock();

#define PRESS_UP        (gInput->GetKeyDown(KEY_UP))
#define PRESS_DOWN      (gInput->GetKeyDown(KEY_DOWN))
#define PRESS_LEFT      (gInput->GetKeyDown(KEY_LEFT))
#define PRESS_RIGHT     (gInput->GetKeyDown(KEY_RIGHT))
#define PRESS_HOME      (gInput->GetKeyDown(KEY_HOME))
#define PRESS_PAGEUP    (gInput->GetKeyDown(KEY_PAGEUP))
#define PRESS_W         (gInput->GetKeyDown(KEY_W))
#define PRESS_S         (gInput->GetKeyDown(KEY_S))
#define PRESS_A         (gInput->GetKeyDown(KEY_A))
#define PRESS_D         (gInput->GetKeyDown(KEY_D))
#define PRESS_Q         (gInput->GetKeyDown(KEY_Q))
#define PRESS_E         (gInput->GetKeyDown(KEY_E))

#define IN_PAUSE        (gScene->GetTimeScale() == M_EPSILON)
