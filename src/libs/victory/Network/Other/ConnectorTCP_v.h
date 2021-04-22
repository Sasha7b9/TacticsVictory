// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include <map>
#include <mutex>
#include <thread>
#include <queue>


// ������ �������
class BaseConnectorTCP
{
public:

    virtual ~BaseConnectorTCP();

    void Release();

    bool Connect(const std::string &host, uint16 port);

    void SetReadTimeOut(uint timeout);

    void SetWriteTimeOut(uint timeout);

    void Disconnect();

    bool IsConnected() const;

    // ������� size ���� �� ������� data
    void Transmit(const void *data, uint size);

    // ������ ������� ����� size ���� � ������ data. ���������� ���������� ������� �������� ����.
    // � ������ ������ ���������� -1
    // ���� size == 0, �� ������ �� ������, � ���������� ���������� ��������� ��� ������ ����
    ssize_t Receive(void *data, uint size);

private:

    std::unique_ptr<sockpp::tcp_connector>  connection;
};


struct TaskMasterServer
{
    pFuncUV    request = 0;             // ���������� �������. ������ ���������� id �������
    pFuncpCpVU handler_answer = 0;      // ���������� ������
    int64      delta_time = 0;          // ����� ����� ���������� ������� ��������� �������
    int64      prev_time = 0;
    int64      last_tive_receive = 0;
    uint       counter = 0xFFFFFFFF;     // ������� ��� ��������� ������

    // ���������� true, ���� ���������� ����������� ������� (��, � ������� ������� == 0)
    static bool ExistCompleted(std::vector<TaskMasterServer *> &tasks);
};

/*
 *   ����� ����� ConnectorTCP �������������� �������������� � �������� �� ������� �������
 */

class ConnectorTCP
{
public:

    void Init(pchar _host, uint16 _port)
    {
        host = _host;
        port = _port;
    };

    void SetCallbacks(pFuncVV fail, pFuncVV connection, pFuncVV disconnection);

    void Connect();

    void Disconnect();

    void SetTasks();

    void Update();

    void Destroy();

    // ������� �������. ������ ������ ���������� ���������� 32-� ������ ���������������, ������� ��������� ��������
    // ������� � ������ �������.
    uint SendRequest(pchar request, const void *data = nullptr, uint size = 0);
    uint SendRequest(pchar request, pchar data);

    bool IsConnected();

    // ��������� ������ ����� �������� ���������� �������
    void SetTask(int64 dT, TaskMasterServer *task);

    // �������� ��������� ������
    void RunTask(TaskMasterServer *task);

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

    std::vector<uint8> data;                        // ����� �������� �������� ������

private:

    BaseConnectorTCP connector;                     // ����� �������� ������ � ������

    std::string host;
    uint16 port;                                    // ���� ������� � ������. ���� ������ �� 1 ������

    std::map<uint, TaskMasterServer *> wait_tasks;  // ������, ��������� ������ (�����������)
    std::vector<TaskMasterServer *>    new_tasks;   // ������, ��������� ���������� (������������ � ������� ���
                                                    // ����������

    bool destroy = false;
    std::mutex  mutex;                      // ������ mutex ����� ��������, ���� ������ ��������� � �������� ����������
    pFuncVV funcFailConnection = nullptr;   // ���������� � ������ ���������� ������� ����������
    pFuncVV funcConnection     = nullptr;   // ���������� � ������ �������� ������� ����������
    pFuncVV funcDisconnection  = nullptr;   // ���������� ��� ������ ����� � ��������

    State::E state = State::Idle;

    uint last_request_id = 0;

    // ��������� ��������� �������
    void ExecuteTasks();

    // ������� ��������� ������
    void ReceiveData();

    // ���������� �������� ������
    void ProcessData();

    // ���������� false, ���� ���������� � �������� ��������
    bool ExistConnection();
};
