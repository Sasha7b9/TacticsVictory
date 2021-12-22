// 2021/12/20 22:29:48 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "TVBattler.h"
#include "Network/Messages/MessagesServer_.h"
#include "Scene/World/GameWorld.h"
#include "Scene/World/Landscape_.h"


using namespace Pi;


void Battler::HandleConnectionEvent(ConnectionEvent event, const NetworkAddress &address, const void *)
{
    switch (event)
    {
    case ConnectionEvent::QueryReceived:
        LOG_WRITE("ConnectionEvent::QueryReceived");
        break;

    case ConnectionEvent::AttemptFailed:
        {
            LOG_ERROR_TRACE("ConnectionEvent::AttemptFailed");
            NetworkAddress localAddress = MessageMgr::StringToAddress(LOCAL_ADDRESS);
            localAddress.SetPort(PORT_NUMBER);
            TheMessageMgr->Connect(localAddress);
        }
        break;

    case ConnectionEvent::ClientOpened:
        LOG_WRITE("ConnectionEvent::ClientOpened");
        break;

    case ConnectionEvent::ServerAccepted:
        LOG_WRITE("Server %s:%d accepted", address.GetStringAddress().c_str(), address.GetPort());
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

    default:
        LOG_ERROR_TRACE("Unknown connection event %d from %s:%d", event, address.GetStringAddress().c_str(), address.GetPort());
    }
}


void Battler::HandleGameEvent(GameEvent event, const void *param)
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


void Battler::HandlePlayerEvent(PlayerEvent event, Player *player, const void *param)
{
    switch (event)
    {
    case PlayerEvent::Connected:
        {
            const NetworkAddress &address = player->GetPlayerAddress();
            LOG_WRITE("Connected to game on %s:%d as player \"%d:%s\"", address.GetStringAddress().c_str(), address.GetPort(), player->GetPlayerKey(), player->GetPlayerName());
        }
        break;

    case PlayerEvent::Disconnected:
        LOG_WRITE("PlayerEvent::Disconnected");
        break;

    case PlayerEvent::TimedOut:
        LOG_WRITE("PlayerEvent::TimedOut");
        break;

    case PlayerEvent::Initialized:
        LOG_WRITE("PlayerEvent::Initialized");
        break;

    case PlayerEvent::ChatReceived:
        LOG_WRITE("PlayerEvent::ChatReceived");
        break;

    case PlayerEvent::Renamed:
        LOG_WRITE("PlayerEvent::Renamed");
        break;

    default:
        LOG_WRITE_TRACE("Unknown player event %d", (int)event);
        break;
    }
}


void Battler::ReceiveMessage(Player *, const NetworkAddress &, const Message *message)
{
    LOG_ERROR_TRACE("Received unknown message type %d", message->GetMessageType());
}


Message *Battler::CreateMessage(PiTypeMessage::E type, Decompressor &) const
{
    switch (type)
    {
    case PiTypeMessage::CreateLandscape:             return new MessageCreateLandscape();         break;
    case PiTypeMessage::CreateGameObject:            return new MessageCreateGameObject();        break;
    case PiTypeMessage::SendGameObjectNodeTransform: return new MessageGameObjectNodeTransform(); break;

    default:
        LOG_ERROR_TRACE("Unkndown message type %d", type);
    }

    return nullptr;
}
