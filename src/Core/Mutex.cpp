#include <stdafx.h>


#include "Mutex.h"


bool Mutex::TryAcquire()
{
    return TryEnterCriticalSection((CRITICAL_SECTION*)handle_) != 0;
}