#pragma once


#ifdef LOG_WRITE
#undef LOG_WRITE
#endif

#define LOG_WRITE(...) Log::Write(__FILE__, __LINE__, __VA_ARGS__);
#define FUNC_ENTER LOG_WRITE("%s enter", __FUNCTION__);
#define FUNC_LEAVE LOG_WRITE("%s leave", __FUNCTION__);

#define LOG_ERROR(...) Log::Write(__FILE__, __LINE__, __VA_ARGS__);


namespace Pi
{

    class Log
    {
    public:
    
        //+V576,class:Log,function:Write,format_arg:3,ellipsis_arg:4
        static void Write(pchar nameFile, int numStr, pchar format, ...);
    };

}