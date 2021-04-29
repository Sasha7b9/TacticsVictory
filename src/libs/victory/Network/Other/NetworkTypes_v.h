// 2021/04/07 20:38:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


// �������������� ������-�������� �������
#define MSG_NTW_PING                "ping"                  // ������ �����
#define MSG_NTW_INFO_LIVINGROOM     "info_livingroom"       // ���� ���������� �������� �������� ������-������� �
                                                            // ���� ���������
#define MSG_NTW_SET_NAME_LIVINGROOM "set_name_livingrom"    // ��������� ����� ��������
                                                            // ������ �������� ����� �������� ������� ������������

#define MSG_NTW_GET                 "get"
#define MSG_NTW_GET_PORT_LIVINGROOM_BROADCAST_UDP           \
                                            MSG_NTW_GET " port livingroom_broadcast_udp"   // ����� ������-�������


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


struct ClientInfo
{
    struct SocketAddress
    {
        void SetHostIP(void *ip);

        // ���������� ������ ����� ������� � ���� "host:port"
        std::string ToStringFull() const;

        // ���������� ������ ip-����� �������
        std::string ToStringHost() const;

        sockaddr_in sin;
    }                        address;   // ����� �������

    std::vector<uint8>       bindata;   // ��������������� �������� ������
    void *benv;      // ����� ������� libevent
    std::vector<uint8>       message;   // ����� �������� �������� ��������� - ������� ������, � ����� ��������������
                                        // ������, ���� ����
    std::vector<std::string> words;     // �������� �� ����� ��������� ����� ���������
    std::string              name;      // ��� ��������, ��� ��� ����� ������������ � ���� ������ ������� � �������

    void *GetRawData();                 // ���������� ��������� �� ������, ���� ������� ������� � ���������

    static uint GetID(std::vector<uint8> &received);

    static uint GetSize(std::vector<uint8> &received);

    // ���������� ����� ������� �� received � data. ��� ���� �� ����������� ������� ������������ ������ ���������
    static void MoveData(std::vector<uint8> &received, std::vector<uint8> &data);
};


struct SockAddrIn
{
    void Init(uint16 family, pchar ip, uint16 port);

    // ���������� ���������� �������� ����
    int RecvFrom(evutil_socket_t socket, char *buffer, int size_buffer);

    char *GetIP();
    uint16 GetPort();

    sockaddr *GetSockAddr();

private:

    sockaddr_in addr = { 0 };
};
