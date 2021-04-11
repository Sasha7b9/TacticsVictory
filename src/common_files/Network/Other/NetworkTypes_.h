// 2021/04/07 20:38:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


// �������������� ������-�������� �������
#define MSG_NTW_PING                "ping"                  // ������ �����
#define MSG_NTW_INFO_LIVINGROOM     "info_livingroom"       // ���� ���������� �������� �������� ������-������� �
                                                            // ���� ���������
#define MSG_NTW_SET_NAME_LIVINGROOM "set_name_livingrom"    // ��������� ����� ��������


// � ����� ���������� ����� ��������� ���������� � �������� �� ������� ������-�������
struct ServerInfo
{
    std::string address = "";
    std::string name = "";
    int         ping = -1;
    int         cpu = -1;

    // ��������� ���������� � ������� � ������ buffer ��� ��������
    void AppendInfo(std::string address, std::string &buffer);

    static void ParseString(const std::string &data, std::vector<ServerInfo> &servers);
};
