// 2021/04/09 14:45:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct ServerInfo;


class Server
{
public:

    void Run();

    void Stop() { run = false; }

    void AppendHandler(pchar command, pFuncVV handler);

    void Prepare();

    static std::map<std::string, pFuncVV> handlers;     // ����� �������� ����������� �������� �� ������� �����

    static std::vector<std::string> words;              // ������������ � ������������

private:

    bool run = true;
};
