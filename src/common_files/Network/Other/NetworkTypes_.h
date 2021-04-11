// 2021/04/07 20:38:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


// ќбрабатываемые мастер-сервером запросы
#define MSG_NTW_PING            "ping"                      // запрос пинга
#define MSG_NTW_INFO_LIVINGROOM "info_livingroom"           // Ётим сообщением гостина€ сообщает мастер-серверу о
                                                            // своЄм состо€нии


// ¬ таких структурах будет хранитьс€ информаци€ о серверах на стороне ћастер-сервера
struct ServerInfo
{
    std::string address = "";
    std::string name = "";
    int         ping = -1;
    int         cpu = -1;

    // ƒобавл€ет информаци€ о сервере в строку buffer дл€ передачи
    void AppendInfo(std::string address, std::string &buffer);

    static void ParseString(const std::string &data, std::vector<ServerInfo> &servers);
};
