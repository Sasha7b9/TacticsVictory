// 2021/04/09 14:45:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


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
    void                    *benv;      // ����� ������� libevent
    std::vector<uint8>       message;   // ����� �������� �������� ��������� - ������� ������, � ����� ��������������
                                        // ������, ���� ����
    std::vector<std::string> words;     // �������� �� ����� ��������� ����� ���������
    std::string              name;      // ��� ��������, ��� ��� ����� ������������ � ���� ������ ������� � �������

    void *GetRawData();                 // ���������� ��������� �� ������, ���� ������� ������� � ���������
};


class ServerTCP
{
public:

    typedef void (*handlerClient) (uint, ClientInfo &);

    void Run(uint16 port);

    void Stop() { run = false; }

    void AppendHandler(pchar command, handlerClient handler);

    void SendAnswer(void *bev, uint id, pchar message, void *data = nullptr, uint size = 0);
    void SendAnswer(void *bev, uint id, pchar message, pchar data);

    std::map<std::string, handlerClient> handlers;   // ����� �������� ����������� �������� �� ������� �����

    std::map<void *, ClientInfo> clients;

private:

    void Prepare();

    bool run = true;

    struct CallbackArgs
    {
        ServerTCP  *server;
        event_base *base;
    };

    // ���������� ��� ����� ����������
    static void CallbackRead(struct bufferevent *, void *arg);
    static void CallbackWrite(struct bufferevent *, void *arg);
    static void CallbackAccept(evutil_socket_t listener, short event, void *arg);
    static void CallbackError(struct bufferevent *bev, short what, void *ctx);
    static void CallbackLog(int, const char *);
};
