// 2021/12/20 22:50:49 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "TVBattle.h"


using namespace Pi;


void Battle::HandleConnectionEvent(ConnectionEvent event, const NetworkAddress &, const void *)
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


Message *Battle::CreateMessage(MessageType::E, Decompressor &) const
{
    LOG_WRITE("Battle::CreateMessage");

    return nullptr;
}


void Battle::ReceiveMessage(Player *, const NetworkAddress &, const Message *)
{
    LOG_WRITE("Battle::ReceiveMessage");
}


void Battle::HandlePlayerEvent(PlayerEvent::E event, Player *player, const void *param)
{
    LOG_WRITE("Battle::HandlePlayerEvent");
}


void Battle::HandleGameEvent(GameEvent::E event, const void *param)
{
    LOG_WRITE("Battle::HandleGameEvent");
}
