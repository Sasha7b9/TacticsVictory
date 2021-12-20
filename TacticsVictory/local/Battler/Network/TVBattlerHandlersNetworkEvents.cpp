// 2021/12/20 22:29:48 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "TVBattler.h"


using namespace Pi;


void Battler::HandleConnectionEvent(ConnectionEvent event, const NetworkAddress &, const void *)
{
    switch (event)
    {
    case ConnectionEvent::QueryReceived:
        LOG_WRITE("ConnectionEvent::QueryReceived");
        break;

    case ConnectionEvent::AttemptFailed:
        LOG_WRITE("ConnectionEvent::AttemptFailed");
        break;

    case ConnectionEvent::ClientOpened:
        LOG_WRITE("ConnectionEvent::ClientOpened");
        break;

    case ConnectionEvent::ServerAccepted:
        LOG_WRITE("ConnectionEvent::ServerAccepted");
        break;

    case ConnectionEvent::ServerClosed:
        LOG_WRITE("ConnectionEvent::ServerClosed");
        break;

    case ConnectionEvent::ClientClosed:
        LOG_WRITE("ConnectionEvent::ClientClosed");
        break;

    case ConnectionEvent::ServerTimedOut:
        LOG_WRITE("ConnectionEvent::ServerTimedOut");
        break;

    case ConnectionEvent::ClientTimedOut:
        LOG_WRITE("ConnectionEvent::ClientTimedOut");
        break;
    }
}
