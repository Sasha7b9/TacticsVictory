// 2021/04/30 20:21:27 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Network/MapLivingRooms.h"


std::map<std::pair<pchar, uint16>, ConnectorUDP> MapLivingRooms::connectors;


void MapLivingRooms::Append(pchar ip, uint16 port)
{
    auto pair = std::make_pair(ip, port);

    connectors[pair] = ConnectorUDP();

    connectors[pair].AcceptServer(ip, port);
}


void MapLivingRooms::SenMessageToAll(pchar message)
{
    for (auto &connector : connectors)
    {
        connector.second.SendMessage(message);
    }
}
