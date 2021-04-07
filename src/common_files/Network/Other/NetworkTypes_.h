// 2021/04/07 20:38:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


// ќбрабатываемые мастер-сервером запросы
#define MSM_CLOSE_CONNECTION     "close connection"         // отконнектитьс€ от master
#define MSM_GET_ADDRESS_UPLOADER "get address uploader"     // вернуть адрес uploader
#define MSM_GET_ADDRESS_HANGAR   "get address hangar"       // вернуть адрес hangar
#define MSM_GET_ADDRESS_DATABASE "get address database"     // вернуть адрес database
#define MSM_GET_ADDRESS_BATTLE   "get address battle"       // вернуть адрес бо€
#define MSG_GET_SERVERS          "get servers"              // возвращает список имеющихс€ серверов
#define MSM_PING                 "ping"                     // запрос пинга
#define MSM_TERMINCATE           "terminate"                // завершить выполнение master


// ¬ таких структурах будет хранитьс€ информаци€ о серверах на стороне ћастер-сервера
struct ServerInfo
{
    std::string name = "";
    std::string address = "";
    int         ping = 0;
    int         cpu = 0;

    bool operator<(const ServerInfo &rhs)
    {
        return name < rhs.name;
    }
};
