// 2021/04/09 14:45:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct ServerInfo;


struct SocketAddress
{
    std::string ToString()
    {
        char buffer[100];

        sprintf_s(buffer, 100, "%d.%d.%d.%d:%d", sin.sin_addr.S_un.S_un_b.s_b1,
            sin.sin_addr.S_un.S_un_b.s_b2,
            sin.sin_addr.S_un.S_un_b.s_b3,
            sin.sin_addr.S_un.S_un_b.s_b4,
            sin.sin_port);

        return std::string(buffer);
    };

    sockaddr_in sin;
};


struct ClientInfo
{
    SocketAddress      address;     // ����� �������
    std::vector<uint8> bindata;     // ��������������� �������� ������
    void              *benv;        // ����� ������� libevent
    std::vector<uint8> message;     // ����� �������� �������� ��������� - ������� ������, � ����� ��������������
                                    // ������, ���� ����
};


class Server
{
public:

    void Run();

    void Stop() { run = false; }

    void AppendHandler(pchar command, pFuncVUpV handler);

    void Prepare();

    void SendAnswer(void *bev, uint id, pchar message);

    static std::map<std::string, pFuncVUpV> handlers;   // ����� �������� ����������� �������� �� ������� �����

    static std::vector<std::string> words;              // ������������ � ������������

private:

    void SendString(void *bev, pchar message);

    bool run = true;
};
