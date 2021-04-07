// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Network/Other/SocketsTCP_.h"


/*
*   ����� MasterServer ������ ������������ ��� ����������, ������� ����� ������ � ������-�������
*/


#define MSM_CLOSE_CONNECTION     "close connection"         // �������������� �� master
#define MSM_GET_ADDRESS_UPLOADER "get address uploader"     // ������� ����� uploader
#define MSM_GET_ADDRESS_HANGAR   "get address hangar"       // ������� ����� hangar
#define MSM_GET_ADDRESS_DATABASE "get address database"     // ������� ����� database
#define MSM_GET_ADDRESS_BATTLE   "get address battle"       // ������� ����� ���
#define MSM_PING                 "ping"                     // ������ �����
#define MSM_TERMINCATE           "terminate"                // ��������� ���������� master


class MasterServer
{
public:

    void SetAddress(pchar full_address) {address = full_address; };

    void SetCallbacks(pFuncVV fail, pFuncVV connection, pFuncVV disconnection);

    void Connect();

    void Destroy();

    std::string GetValue(pchar key);

    bool IsConnected();

    pchar GetAddress() const { return address.c_str(); }

    void Update();

    struct State { enum E {
        Idle,                   // �������
        NeedConnection,         // ����� ����������
        AttemptConnection,      // � �������� ����������
        InConnection,           // ����������
        WaitPing                // �������� ��������� � �����
    }; };

private:

    ConnectorTCP connector;     // ����������� ��� ����� � �������� ������-��������
    bool destroy = false;
    std::mutex  mutex;          // ������ mutex ����� ��������, ���� ������ ��������� � �������� ����������
    std::string address;
    pFuncVV funcFailConnection = nullptr;   // ���������� � ������ ���������� ������� ����������
    pFuncVV funcConnection     = nullptr;   // ���������� � ������ �������� ������� ����������
    pFuncVV funcDisconnection  = nullptr;   // ���������� ��� ������ ����� � ��������

    State::E state = State::Idle;
};
