// 2021/04/08 16:17:52 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class LivingRoom
{
public:

    int Run(pchar ip);

    // ������� ��� ��� ������-�������
    void SendNameToMasterServer();

private:

    int RunRemoteServer();

    int MainCycle();

    pchar remoteMasterIP = nullptr;     // ����� ��������� ������-�������
};
