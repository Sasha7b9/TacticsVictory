// 2021/04/30 20:21:27 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Network/MapLivingRooms.h"


std::map<pchar, ConnectorUDP> MapLivingRooms::connectors;


void MapLivingRooms::Append(pchar ip, uint16 port)
{
    auto pair = std::make_pair(ip, port);

    connectors[ip] = ConnectorUDP();

    // TheLivingRoomUDP.AcceptServer(TheSettings.GetString("master_server", "host"), 40001);
}


void MapLivingRooms::SenMessageToAll(pchar message)
{
    // TheLivingRoomUDP.SendMessage(message.c_str());
}
