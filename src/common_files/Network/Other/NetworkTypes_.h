// 2021/04/07 20:38:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


// �������������� ������-�������� �������
#define MSM_CLOSE_CONNECTION     "close connection"         // �������������� �� master
#define MSM_GET_ADDRESS_UPLOADER "get address uploader"     // ������� ����� uploader
#define MSM_GET_ADDRESS_HANGAR   "get address hangar"       // ������� ����� hangar
#define MSM_GET_ADDRESS_DATABASE "get address database"     // ������� ����� database
#define MSM_GET_ADDRESS_BATTLE   "get address battle"       // ������� ����� ���
#define MSG_GET_LIVINGROMS       "get livingrooms"          // ���������� ������ ��������� ��������
#define MSM_PING                 "ping"                     // ������ �����
#define MSM_TERMINCATE           "terminate"                // ��������� ���������� master


// � ����� ���������� ����� ��������� ���������� � �������� �� ������� ������-�������
struct ServerInfo
{
    std::string name = "";
    int         ping = 0;
    int         cpu = 0;

    // ��������� ���������� � ������� � ������ buffer ��� ��������
    void AppendInfo(std::string address, std::string &buffer);
};
