// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once 


typedef void(*pFuncVV)();
typedef float(*pFuncFV)();
typedef void(*pFuncVF)(float);


typedef unsigned char   uint8;
typedef long long int   int64;
typedef unsigned long long uint64;
typedef short unsigned  uint16;
typedef unsigned int    uint;
typedef unsigned short  ushort;
typedef unsigned char   uchar;


#define DEFAULT_MEMBERS(name) name& operator=(const name&) = delete; name(const name&) = delete


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

#define SERVER_ADDRESS  "127.0.0.1"
#define SERVER_PORT     1000


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

#ifdef _DEBUG
#define PROFILER_FUNC_ENTER     TheProfiler->BeginBlock(__FUNCTION__);
#define PROFILER_FUNC_LEAVE     TheProfiler->EndBlock();
#else
#define PROFILER_FUNC_ENTER
#define PROFILER_FUNC_LEAVE
#endif

#define PRESS_UP        (TheInput->GetKeyDown(KEY_UP))
#define PRESS_DOWN      (TheInput->GetKeyDown(KEY_DOWN))
#define PRESS_LEFT      (TheInput->GetKeyDown(KEY_LEFT))
#define PRESS_RIGHT     (TheInput->GetKeyDown(KEY_RIGHT))
#define PRESS_HOME      (TheInput->GetKeyDown(KEY_HOME))
#define PRESS_PAGEUP    (TheInput->GetKeyDown(KEY_PAGEUP))
#define PRESS_W         (TheInput->GetKeyDown(KEY_W))
#define PRESS_S         (TheInput->GetKeyDown(KEY_S))
#define PRESS_A         (TheInput->GetKeyDown(KEY_A))
#define PRESS_D         (TheInput->GetKeyDown(KEY_D))
#define PRESS_Q         (TheInput->GetKeyDown(KEY_Q))
#define PRESS_E         (TheInput->GetKeyDown(KEY_E))

#define KEY_IS_F1       (key == KEY_F1)
#define KEY_IS_F10      (key == KEY_F10)
#define KEY_IS_F11      (key == KEY_F11)
#define KEY_IS_ESC      (key == KEY_ESCAPE)
#define KEY_IS_SPACE    (key == KEY_SPACE)
#define KEY_IS_UP       (key == KEY_UP)
#define KEY_IS_DOWN     (key == KEY_DOWN)
#define KEY_IS_LEFT     (key == KEY_LEFT)
#define KEY_IS_RIGHT    (key == KEY_RIGHT)
#define KEY_IS_KP_MINUS (key == KEY_KP_MINUS)
#define KEY_IS_KP_PLUS  (key == KEY_KP_PLUS)
#define KEY_IS_9        (key == KEY_9)
#define KEY_IS_I        (key == KEY_I)

#define IN_PAUSE        (TheScene->GetTimeScale() <= M_EPSILON)

typedef enum
{
    ModeApp_Start,
    ModeApp_Server,
    ModeApp_Client
} ModeApp;

#define MODE_CLIENT (TheMode == ModeApp_Client)
#define MODE_SERVER (TheMode == ModeApp_Server)
#define MODE_START  (TheMode == ModeApp_Start)

// Имена узлов

#define NODE_CAMERA_TARGET "CameraTarget"

#define UNUSED(x) (void)(x)
