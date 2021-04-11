// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Network/Other/SocketsTCP_.h"


/*
 *   ����� ����� ServerConnector �������������� �������������� � �������� �� ������� �������
 */


struct TaskMasterServer
{
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
    void SendRequest(pchar request, const void *data = nullptr, uint size = 0);

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
        EventDisconnect,        // ������� ������ ����� � ������-��������
        GetPing                 // ������� ����
    }; };

    std::vector<uint8> data;        // ����� �������� �������� ������

private:

    ConnectorTCP connector;         // ����� �������� ������ � ������

    std::string host;
    uint16 port;                    // ���� ������� � ������. ���� ������ �� 1 ������

    std::vector<TaskMasterServer *> all_tasks;      // ����� ������������ ����������� ������

    bool destroy = false;
    std::mutex  mutex;              // ������ mutex ����� ��������, ���� ������ ��������� � �������� ����������
    pFuncVV funcFailConnection = nullptr;   // ���������� � ������ ���������� ������� ����������
    pFuncVV funcConnection     = nullptr;   // ���������� � ������ �������� ������� ����������
    pFuncVV funcDisconnection  = nullptr;   // ���������� ��� ������ ����� � ��������
    pFuncVI funcPing           = nullptr;

    State::E state = State::Idle;

    uint last_request_id = 0;

    void ExecuteTasks();

    // ������� ��������� ������
    void ReceiveData();

    // ���������� �������� ������
    void ProcessData();
};
