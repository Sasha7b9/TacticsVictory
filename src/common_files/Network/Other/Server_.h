// 2021/04/09 14:45:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct ServerInfo;


class Server
{
public:

    void Run();

    void Stop() { run = false; }

    void AppendHandler(pchar command, pFuncVV handler);

    void AppendServerInfo(const ServerInfo &info);

private:

    void Prepare();

    bool run = true;
};
