// 2021/02/23 22:42:59 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


// В этой переменой ноды будет храниться имя типа игрового объекта
#define VAR_OBJECT_TYPE_NAME    "Object type name"

#define VAR_NODE_IS_UNIT        "isUnit"
#define VAR_NODE_IS_FLYING      "isFlaying"

#define NAME_NODE_CAMERA_TARGET "CameraTarget"
#define NAME_NODE_TERRAIN       "Terrain"
#define NAME_NODE_TILE_PATH     "TilePath"

#define RESOURCES_DIR           "TVData"

#define SERVER_ADDRESS          "62.109.6.164"
//#define SERVER_ADDRESS          "127.0.0.1"
#define SERVER_PORT             40000

#define VIEW_MASK_FOR_MISSILE   1
#define VIEW_MASK_FOR_EFFECTS   2

#define CALL_MEMBER_IF_EXIST(object, function) if(object) (object)->function()

#define GAME_IN_PAUSE        (TheScene->GetTimeScale() <= M_EPSILON)

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

#define UNUSED(x) (void)x
