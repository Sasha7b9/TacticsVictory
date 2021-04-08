// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Network/Other/SocketsTCP_.h"


/*
*   ����� ServerT ������ ������������ ��� ����������, ������� ����� ������ � ������-�������
*/


struct TaskMasterServer
{
    int         count;          // ������� ��� ��������� ������� (0 - ����������)
    int64       delta_time;     // ����� ����� ���������� ������� ��������� �������
    pFuncVV     func;           // ��������� ������ �� ������-�������
    int64       prev_time;
};


class ServerT
{
public:

    void SetAddress(pchar _ip, uint16 _port) { ip = _ip; port_out = _port; };

    void SetCallbacks(pFuncVV fail, pFuncVV connection, pFuncVV disconnection, pFuncVI ping);

    void Connect();

    void Destroy();

    std::string GetAnswer(pchar key);

    void SendString(pchar string);

    std::string GetAnswer();

    bool IsConnected();

    void Update();

    // ��������� ������ ����� �������� ���������� �������
    void SetTask(TaskMasterServer *task);

    struct State { enum E {
        Idle,                   // �������
        NeedConnection,         // ����� ����������
        AttemptConnection,      // � �������� ����������
        EventConnection,        // ��������� ����������, ����� �������� ������� funcConnection
        EventFailConnection,    // ��������� ����������, ����� �������� ������� funcFailConnection
        InConnection,           // ����������
        WaitPing,               // �������� ��������� � �����
        EventDisconnect,        // ������� ������ ����� � ������-��������
        GetPing                 // ������� ����
    }; };

private:

    ConnectorTCP connOUT;       // ����� �������� ������ � ������
    ConnectorTCP connIN;        // ���� ��������� ������ �� �������

    std::string ip;
    uint16 port_out;            // ���� ������� � ������. ���� ������ �� 1 ������

    bool destroy = false;
    std::mutex  mutex;          // ������ mutex ����� ��������, ���� ������ ��������� � �������� ����������
    pFuncVV funcFailConnection = nullptr;   // ���������� � ������ ���������� ������� ����������
    pFuncVV funcConnection     = nullptr;   // ���������� � ������ �������� ������� ����������
    pFuncVV funcDisconnection  = nullptr;   // ���������� ��� ������ ����� � ��������
    pFuncVI funcPing           = nullptr;

    State::E state = State::Idle;

    void ExecuteTasks(int64 now);
};
