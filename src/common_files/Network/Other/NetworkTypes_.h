// 2021/04/07 20:38:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


// Обрабатываемые мастер-сервером запросы
#define MSM_CLOSE_CONNECTION     "close connection"         // отконнектиться от master
#define MSM_GET_ADDRESS_UPLOADER "get address uploader"     // вернуть адрес uploader
#define MSM_GET_ADDRESS_HANGAR   "get address hangar"       // вернуть адрес hangar
#define MSM_GET_ADDRESS_DATABASE "get address database"     // вернуть адрес database
#define MSM_GET_ADDRESS_BATTLE   "get address battle"       // вернуть адрес боя
#define MSM_GET_LIVINGROMS       "get livingrooms"          // возвращает список доступных гостиных
#define MSM_PING                 "ping"                     // запрос пинга
#define MSM_SEND_LIVINGROOM_INFO "send livingroom info"
#define MSM_TERMINCATE           "terminate"                // завершить выполнение master


// В таких структурах будет храниться информация о серверах на стороне Мастер-сервера
struct ServerInfo
{
    std::string address = "";
    std::string name = "";
    int         ping = 0;
    int         cpu = 0;

    // Добавляет информация о сервере в строку buffer для передачи
    void AppendInfo(std::string address, std::string &buffer);

    static void ParseString(const std::string &data, std::vector<ServerInfo> &servers);
};
