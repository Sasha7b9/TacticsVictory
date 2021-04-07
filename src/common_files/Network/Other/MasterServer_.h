// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Network/Other/SocketsTCP_.h"


/*
*   Класс MasterServer должны использовать все приложения, которым нужен доступ к мастер-серверу
*/


#define MSM_CLOSE_CONNECTION     "close connection"         // отконнектиться от master
#define MSM_GET_ADDRESS_UPLOADER "get address uploader"     // вернуть адрес uploader
#define MSM_GET_ADDRESS_HANGAR   "get address hangar"       // вернуть адрес hangar
#define MSM_GET_ADDRESS_DATABASE "get address database"     // вернуть адрес database
#define MSM_GET_ADDRESS_BATTLE   "get address battle"       // вернуть адрес боя
#define MSM_PING                 "ping"                     // запрос пинга
#define MSM_TERMINCATE           "terminate"                // завершить выполнение master


class MasterServer
{
public:

    void SetAddress(pchar full_address) {address = full_address; };

    void Connect();

    void Destroy();

    std::string GetValue(pchar key);

    bool IsConnected();

    pchar GetAddress() const { return address.c_str(); }

private:

    ConnectorTCP connector;             // Соединитель для связи с удалённым мастер-сервером

    bool destroy = false;

    std::mutex mutex;                   // Данный mutex будет захвачен, пока сервер находится в процессе соединения

    std::string address;
};
