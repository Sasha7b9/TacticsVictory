// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Network/Other/SocketsTCP_.h"


/*
*   ����� MasterServer ������ ������������ ��� ����������, ������� ����� ������ � ������-�������
*/


struct TaskMasterServer
{
    int         count;          // ������� ��� ��������� ������� (0 - ����������)
    int64        delta_time;     // ����� ����� ���������� ������� ��������� �������
    int64        prev_time;
    std::string request;        // ����������� ������
    pFuncVpCh   process;        // ��������� ������ �� ������-�������
};


class MasterServer
{
public:

    void SetAddress(pchar full_address) {address = full_address; };

    void SetCallbacks(pFuncVV fail, pFuncVV connection, pFuncVV disconnection, pFuncVI ping);

    void Connect();

    void Destroy();

    std::string GetValue(pchar key);

    bool IsConnected();

    pchar GetAddress() const { return address.c_str(); }

    void Update();

    void AppendTask(TaskMasterServer *task);

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

    ConnectorTCP connector;     // ����������� ��� ����� � �������� ������-��������
    bool destroy = false;
    std::mutex  mutex;          // ������ mutex ����� ��������, ���� ������ ��������� � �������� ����������
    std::string address;
    pFuncVV funcFailConnection = nullptr;   // ���������� � ������ ���������� ������� ����������
    pFuncVV funcConnection     = nullptr;   // ���������� � ������ �������� ������� ����������
    pFuncVV funcDisconnection  = nullptr;   // ���������� ��� ������ ����� � ��������
    pFuncVI funcPing           = nullptr;

    State::E state = State::Idle;
};
