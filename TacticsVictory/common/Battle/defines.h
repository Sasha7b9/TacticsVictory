// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once

#define SAFE_DELETE(x) if(x) { delete(x); (x) = nullptr; };
#define SAFE_DELETE_ARRAY(x) if (x) { delete [] (x); (x) = nullptr; };
#define SAFE_RELEASE(x) if(x) { (x)->Release(); (x) = nullptr; };

typedef const char * pchar;

typedef unsigned int    uint;
typedef unsigned long   ulong;
