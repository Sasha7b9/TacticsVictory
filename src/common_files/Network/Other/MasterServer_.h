// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Network/Other/SocketsTCP_.h"


/*
*   Класс MasterServer должны использовать все приложения, которым нужен доступ к мастер-серверу
*/


#define MSM_GET_ADDRESS_UPLOADER "get address uploader"      // вернуть адрес uploader
#define MSM_GET_ADDRESS_HANGAR   "get address hangar"        // вернуть адрес hangar
#define MSM_GET_ADDRESS_DATABASE "get address database"      // вернуть адрес database
#define MSM_GET_ADDRESS_BATTLE   "get address battle"        // вернуть адрес боя
#define MSM_CLOSE_CONNECTION     "close connection"          // отконнектиться от master
#define MSM_TERMINCATE           "terminate"                 // завершить выполнение master


class MasterServer
{
public:

    // Делает попытку присоединения к серверу
    void Connect(pchar full_address);

    void Destroy();

    std::string GetValue(pchar key);

private:

    ConnectorTCP connector;             // Соединитель для связи с удалённым мастер-сервером

    bool destroy = false;
    std::mutex mutex;                   // Данный mutex будет захвачен, пока сервер находится в процессе соединения
};
