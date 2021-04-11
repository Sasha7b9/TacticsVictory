// 2021/04/09 14:45:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct ClientInfo
{
    struct SocketAddress
    {
        std::string ToString() const;

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


class Server
{
public:

    typedef void (*handlerClient) (uint, ClientInfo &);

    void Run(uint16 port);

    void Stop() { run = false; }

    void AppendHandler(pchar command, handlerClient handler);

    void Prepare();

    void SendAnswer(void *bev, uint id, pchar message, void *data = nullptr, uint size = 0);

    static std::map<std::string, handlerClient> handlers;   // ����� �������� ����������� �������� �� ������� �����

private:

    bool run = true;
};
