// 2021/04/30 20:21:49 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Network/Other/ConnectorUDP_v.h"
#include <map>


// Набор имеющихся гостиных
class MapLivingRooms
{
public:

    static void Append(pchar ip);

    static void SetPort(uint16 p) { port = p; }

    static void Update();

    static void SenMessageToAll(pchar message);

    // Обрабатывает полученную от мастер-сервера информацию о доступных гостиных
    static void ParseInfo(pchar data);

private:

    static std::map<std::pair<pchar, uint16>, ConnectorUDP> connectors;

    static uint16 port;

    // Установить задания для всех гостиных
    static void SetTasks();
};
