// 2021/02/23 22:42:59 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


// В этой переменой ноды будет храниться имя типа игрового объекта
#define VAR_OBJECT_TYPE_NAME    "Object type name"

#define VAR_NODE_IS_UNIT        "isUnit"
#define VAR_NODE_IS_FLYING      "isFlaying"
#define VAR_NODE_IS_BUILDING    "isBuilding"

#define NAME_NODE_CAMERA_TARGET "CameraTarget"
#define NAME_NODE_TERRAIN       "Terrain"
#define NAME_NODE_TILE_PATH     "TilePath"

#define RESOURCES_DIR           "TVData"

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
typedef unsigned char      uint8;
typedef short unsigned     uint16;
typedef unsigned int       uint;
typedef unsigned long long uint64;
typedef long long          int64;
typedef const char        *pchar;

typedef void (*pFuncVV)();
typedef void (*pFuncVI)(int);
typedef float(*pFuncFV)();
typedef void (*pFuncVF)(float);
typedef void (*pFuncVpCh)(pchar);

#define UNUSED(x) (void)x

#define SAFE_DELETE(x) if(x != nullptr) { delete x; x = nullptr; }


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

#define VAR_MENU_EVENT         "VAR_MENU_EVENT"
#define VAR_GUI_NO_TRANSLATE   "VAR_GUI_NO_TRANSLATE"

#define DELTA_PORT_MASTER_IN      0     // Порт входящих сообщений мастер-сервера
#define DELTA_PORT_MASTER_OUT     1     // Порт исходящих сообщений мастер-сервера
#define DELTA_PORT_UPLOADER_IN    2     // На этот порт uploader принимает сообщения
#define DELTA_PORT_UPLOADER_OUT   3     // С этого порта uploader посылает сообщения
#define DELTA_PORT_DATABASE_IN    4     // В этот порт база данных принимает сообщения
#define DELTA_PORT_DATABASE_OUT   5     // С этого порта база данных отправляет сообщения
#define DELTA_PORT_LIVINGROOM_IN  6
#define DELTA_PORT_LIVINGROOM_OUT 7
