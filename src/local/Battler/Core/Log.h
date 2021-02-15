/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once

#define LOG(format, ...) Log::Write(LOG_INFO, ToString(format, ##__VA_ARGS__));

class Log
{
public:
private:
};
