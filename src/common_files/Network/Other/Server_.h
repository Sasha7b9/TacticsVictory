// 2021/04/09 14:45:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class Server
{
public:

    void Run();

    void AppendHandler(pchar command, pFuncVV handler);

private:

    void Prepare();
};