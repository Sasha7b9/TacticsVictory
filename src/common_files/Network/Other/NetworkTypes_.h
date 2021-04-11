// 2021/04/07 20:38:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


// Обрабатываемые мастер-сервером запросы
#define MSM_PING                 "ping"                     // запрос пинга


// В таких структурах будет храниться информация о серверах на стороне Мастер-сервера
struct ServerInfo
{
    std::string address = "";
    std::string name = "";
    int         ping = -1;
    int         cpu = -1;

    // Добавляет информация о сервере в строку buffer для передачи
    void AppendInfo(std::string address, std::string &buffer);

    static void ParseString(const std::string &data, std::vector<ServerInfo> &servers);
};
