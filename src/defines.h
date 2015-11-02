#pragma once


typedef float(*pFuncFV)();
typedef void(*pFuncVF)(float);
typedef void(*pFuncVI)(int);

typedef long int int64;
typedef short unsigned uint16;

#define SAFE_DELETE(x) if(x) delete x; x = nullptr;
#define SAFE_DELETE_ARRAY(x) if(x) delete[]x; x = nullptr;

#define NODE_TERRAIN "Terrain"
