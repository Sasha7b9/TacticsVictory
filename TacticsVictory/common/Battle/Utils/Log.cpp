#include <stdafx.h>
#include "Log.h"


namespace Pi
{

    void Log::Write(pchar nameFile, int numStr, pchar format, ...)
    {
        static char buffer[4096];
        va_list args;
        va_start(args, format);
        vsprintf(buffer, format, args);
        va_end(args);
        static char buffer2[4096 * 2];
    #ifndef PiLINUX
    #pragma warning(push)
    #pragma warning(disable:4996)
    #endif
        sprintf(buffer2, "%s - \t\t\t\t%s:%d\n", buffer, nameFile, numStr);
    #ifndef PiLINUX
    #pragma warning(pop)
    #endif
        TheEngine->Report(buffer2);
    }

}
