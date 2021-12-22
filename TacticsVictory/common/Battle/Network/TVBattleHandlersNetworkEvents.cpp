// 2021/12/20 22:50:49 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "TVBattle.h"
#include "Network/Messages/MessagesServer_.h"
#include "Network/Messages/MessagesClient_.h"
#include "Scene/World/Landscape_.h"


using namespace Pi;


void Battle::HandleConnectionEvent(ConnectionEvent event, const NetworkAddress &address, const void *)
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
        LOG_WRITE("Client %s:%d is opened", address.GetStringAddress().c_str(), address.GetPort());
        break;

    case ConnectionEvent::ServerAccepted:
        LOG_WRITE("ConnectionEvent::ServerAccepted");
        break;

    case ConnectionEvent::ServerClosed:
        LOG_WRITE("ConnectionEvent::ServerClosed");
        break;

    case ConnectionEvent::ClientClosed:
        LOG_WRITE("Client %s:%d is closed", address.GetStringAddress().c_str(), address.GetPort());
        break;

    case ConnectionEvent::ServerTimedOut:
        LOG_WRITE("ConnectionEvent::ServerTimedOut");
        break;

    case ConnectionEvent::ClientTimedOut:
        LOG_WRITE("ConnectionEvent::ClientTimedOut");
        break;

    default:
        LOG_ERROR_TRACE("Unknown connection event %d from %s:%d", event, address.GetStringAddress().c_str(), address.GetPort());
        break;
    }
}


void Battle::HandleGameEvent(GameEvent event, const void *param)
{
    if (event == GameEvent::GameSynchronized)
    {
        LOG_WRITE("Game is sinchronized");
    }
    else
    {
        LOG_ERROR_TRACE("Unknown game event %d", event);
    }
}


void Battle::HandlePlayerEvent(PlayerEvent event, Player *player, const void *param)
{
    switch (event)
    {
    case PlayerEvent::Connected:
        {
            const NetworkAddress &address = player->GetPlayerAddress();
            LOG_WRITE("Player \"%d:%s\" from %s:%d is connected", player->GetPlayerKey(), player->GetPlayerName(), address.GetStringAddress().c_str(), address.GetPort());
        }
        break;

    case PlayerEvent::Disconnected:
        LOG_WRITE("Player \"%d:%s\" is disconnected", player->GetPlayerKey(), player->GetPlayerName());
        break;

    case PlayerEvent::TimedOut:
        LOG_WARNING("Player \"%d:%s\" is timeout", player->GetPlayerKey(), player->GetPlayerName());
        break;

    case PlayerEvent::Initialized:
        // Здесь мы оказываемся, когда новый игрок подключён и игре и готов к получению состояния
        LOG_WRITE("Player \"%d:%s\" is initialized", player->GetPlayerKey(), player->GetPlayerName());

        TheMessageMgr->SendMessage(player->GetPlayerKey(), MessageCreateLandscape(Landscape::self->GetNameFile()));

        break;

    case PlayerEvent::ChatReceived:
        LOG_WRITE("Player \"%d:%s\" is chat received", player->GetPlayerKey(), player->GetPlayerName());
        break;

    case PlayerEvent::Renamed:
        LOG_WRITE("Player \"%d:%s\" is renamed", player->GetPlayerKey(), player->GetPlayerName());
        break;

    default:
        LOG_ERROR_TRACE("Unknown player event %d", (int)event);
        break;
    }
}


void Battle::ReceiveMessage(Player *, const NetworkAddress &, const Message *message)
{
    LOG_ERROR_TRACE("Unknown type message %d", message->GetMessageType());
}


Message *Battle::CreateMessage(PiTypeMessage::E type, Decompressor &) const
{
    switch (type)
    {
    case PiTypeMessage::RequestGameObjects: return new MessageRequestGameObjects(); break;

    default:
        LOG_ERROR_TRACE("Unknown type message %d", type);
        break;
    }

    return nullptr;
}
