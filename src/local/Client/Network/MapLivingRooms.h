// 2021/04/30 20:21:49 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Network/Other/ConnectorUDP_v.h"
#include <map>


// Набор имеющихся гостиных
class MapLivingRooms
{
public:

    static void Append(pchar ip, uint16 port);

    static void SenMessageToAll(pchar message);

private:

    static std::map<pchar, ConnectorUDP> connectors;
};
