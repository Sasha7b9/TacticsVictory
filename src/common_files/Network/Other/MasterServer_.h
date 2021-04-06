// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Network/Other/SocketsTCP_.h"


/*
*    ласс MasterServer должны использовать все приложени€, которым нужен доступ к мастер-серверу
*/


#define MSM_GET_ADDRESS_UPLOADER "get address uploader"      // вернуть адрес uploader
#define MSM_GET_ADDRESS_HANGAR   "get address hangar"        // вернуть адрес hangar
#define MSM_GET_ADDRESS_DATABASE "get address database"      // вернуть адрес database
#define MSM_GET_ADDRESS_BATTLE   "get address battle"        // вернуть адрес бо€
#define MSM_CLOSE_CONNECTION     "close connection"          // отконнектитьс€ от master
#define MSM_TERMINCATE           "terminate"                 // завершить выполнение master


class MasterServer
{
public:

    // callback вызываетс€ после удачной либо неудачной попытки подключени€ (из Connect())
    MasterServer(pFuncVV callback);

    // ƒелает попытку присоединени€ к серверу
    void Connect(pchar full_address);

    void Destroy();

    std::string GetValue(pchar key);

    bool IsConnected() const;

private:

    ConnectorTCP connector;             // —оединитель дл€ св€зи с удалЄнным мастер-сервером

    bool destroy = false;
    std::mutex mutex;                   // ƒанный mutex будет захвачен, пока сервер находитс€ в процессе соединени€
};
