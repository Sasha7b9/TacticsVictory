#pragma once

#define SAFE_DELETE(x) if(x) { delete(x); (x) = nullptr; };
#define SAFE_DELETE_ARRAY(x) if (x) { delete [] (x); (x) = nullptr; };
#define SAFE_RELEASE(x) if(x) { (x)->Release(); (x) = nullptr; };

typedef const char * pchar;

typedef unsigned int    uint;
typedef unsigned long   ulong;

template <class T>
int Sign(T x) {
    if (x > T(0)) {
        return 1;
    } else if (x < T(0)) {
        return -1;
    } else {
        return 0;
    }
}
