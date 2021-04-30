// 2021/04/06 22:47:26 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Client.h"
#include "Network/Other/ConnectorTCP_v.h"
#include "Network/Other/ConnectorUDP_v.h"
#include "Utils/GlobalFunctions_.h"


void Client::HandlerUpdate(StringHash, VariantMap &)
{
    int64 prev_time = -100000;

    if (GF::Timer::TimeMS() - prev_time > 2000)
    {
        prev_time = GF::Timer::TimeMS();

        TheLivingRoomUDP.SendMessage("Test message");
    }
}

void Client::HandlerPostRenderUpdate(StringHash, VariantMap &)
{

}
