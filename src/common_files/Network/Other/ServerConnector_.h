// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Network/Other/SocketsTCP_.h"


/*
 *   ����� ����� ServerConnector �������������� �������������� � �������� �� ������� �������
 */


struct TaskMasterServer
{
    int         count;          // ������� ��� ��������� ������� (0 - ����������)
    int64       delta_time;     // ����� ����� ���������� ������� ��������� �������
    pFuncVV     func;           // ��������� ������ �� ������-�������
    int64       prev_time;
};


class ServerConnector
{
public:

    void SetAddress(pchar _host, uint16 _port)
    {
        host = _host;
        port = _port;
    };

    void SetCallbacks(pFuncVV fail, pFuncVV connection, pFuncVV disconnection, pFuncVI ping);

    void Connect();

    void Update();

    void Destroy();

    // ������� �������. ������ ������ ���������� ���������� 32-� ������ ���������������, ������� ��������� ��������
    // ������� � ������ �������.
    void SendRequest(pchar request);

    std::string GetAnswer();

    bool IsConnected();

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

    ConnectorTCP connector;         // ����� �������� ������ � ������

    std::string host;
    uint16 port;                    // ���� ������� � ������. ���� ������ �� 1 ������

    std::vector<TaskMasterServer *> tasks;

    bool destroy = false;
    std::mutex  mutex;              // ������ mutex ����� ��������, ���� ������ ��������� � �������� ����������
    pFuncVV funcFailConnection = nullptr;   // ���������� � ������ ���������� ������� ����������
    pFuncVV funcConnection     = nullptr;   // ���������� � ������ �������� ������� ����������
    pFuncVV funcDisconnection  = nullptr;   // ���������� ��� ������ ����� � ��������
    pFuncVI funcPing           = nullptr;

    State::E state = State::Idle;

    uint last_request_id = 0;

    void ExecuteTasks();

    void SendString(pchar string);
};
