// 2021/04/03 13:00:00 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "LivingRoom.h"
#include "FileSystem/ConfigurationFile_.h"
#include "Network/Other/ConnectorTCP_.h"
#include "Network/Other/ServerUDP_.h"


extern ConfigurationFile  TheSettings;
extern LivingRoom         TheLivingRoom;
extern ConnectorTCP       TheMaster;        // Для связи с мастер-сервером
extern ServerUDP          TheServer;        // Для обратной связи с клиентами
