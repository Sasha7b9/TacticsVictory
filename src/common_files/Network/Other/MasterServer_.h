// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Network/Other/SocketsTCP_.h"


/*
*   ����� MasterServer ������ ������������ ��� ����������, ������� ����� ������ � ������-�������
*/


#define MSM_GET_ADDRESS_UPLOADER "get address uploader"      // ������� ����� uploader
#define MSM_GET_ADDRESS_HANGAR   "get address hangar"        // ������� ����� hangar
#define MSM_GET_ADDRESS_DATABASE "get address database"      // ������� ����� database
#define MSM_GET_ADDRESS_BATTLE   "get address battle"        // ������� ����� ���
#define MSM_CLOSE_CONNECTION     "close connection"          // �������������� �� master
#define MSM_TERMINCATE           "terminate"                 // ��������� ���������� master


class MasterServer
{
public:

    // ������ ������� ������������� � �������
    void Connect(pchar full_address);

    void Destroy();

    std::string GetValue(pchar key);

private:

    ConnectorTCP connector;             // ����������� ��� ����� � �������� ������-��������

    bool destroy = false;
    std::mutex mutex;                   // ������ mutex ����� ��������, ���� ������ ��������� � �������� ����������
};
