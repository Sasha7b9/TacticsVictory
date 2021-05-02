// 2021/04/30 20:21:27 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/MapLivingRooms.h"
#include "GUI/Menu/Menu.h"
#include "Utils/GlobalFunctions_.h"
#include "Utils/StringUtils_v.h"


std::map<std::pair<pchar, uint16>, ConnectorUDP> MapLivingRooms::connectors;

uint16 MapLivingRooms::port = 0;


void MapLivingRooms::Append(pchar ip)
{
    auto pair = std::make_pair(ip, port);

    connectors[pair] = ConnectorUDP();

    connectors[pair].AcceptServer(ip, port);
}


void MapLivingRooms::Update()
{
    static int64 prev_time = -100000;

    if (GF::Timer::TimeMS() - prev_time > 2000)
    {
        prev_time = GF::Timer::TimeMS();

        static int counter = 0;

        std::string message("Test message ");
        message += GF::IntToString(++counter, 0);

        SenMessageToAll(message.c_str());
    }
}


void MapLivingRooms::SenMessageToAll(pchar message)
{
    if (port == 0)
    {
        LOGERRORF("Can not sending. Port is not set");
    }

    for (auto &connector : connectors)
    {
        connector.second.Send(message);
    }
}


void MapLivingRooms::ParseInfo(void *data)
{
    LOGWRITE((char *)data);

//    TheMenu->pageFindServer->SetServersInfo((char *)data);
//
//    std::string info((char *)data);
//
//    size_t pos = info.find('|');
//
//    while (pos != std::string::npos)
//    {
//        std::string info_server = info.substr(0, pos);
//
//        std::vector<std::string> words;
//
//        SU::SplitToWords(info_server.c_str(), words, ",|");
//
//        if (words.size() > 1)
//        {
//            Append(words[1].c_str());
//        }
//
//        info.erase(0, pos + 1);
//
//        pos = info.find('|');
//    }
//
//    SetTasks();
}
