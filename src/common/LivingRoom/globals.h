// 2021/04/03 13:00:00 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "LivingRoom.h"
#include "FileSystem/ConfigurationFile_v.h"
#include "Network/Other/ConnectorTCP_v.h"
#include "Network/Other/ServerUDP_v.h"


extern ConfigurationFile  TheSettings;
extern LivingRoom         TheLivingRoom;
extern ConnectorTCP       TheConnMaster;            // Для связи с мастер-сервером
extern ServerUDP          TheBroadcastServerUDP;    // Для обратной связи с клиентами
