// 2021/12/4 22:36:23 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "TVBattler.h"
#include "Scene/World/GameWorld.h"
#include "Scene/World/Landscape_.h"
#include "Network/Messages/MessagesClient_.h"
#include "GameState.h"


using namespace Pi;


void Battler::HandleDisplayEvent(const DisplayEventData *eventData, void * /*cookie*/)
{
    if (eventData->eventType == EventDisplay::Change)
    {
    }
}


void Battler::ApplicationTask()
{
    static bool first = true;

    if (first)
    {
        first = false;

        TheMessageMgr->EndGame();

        TheNetworkMgr->NetworkTask();

        TheNetworkMgr->SetProtocol(kGameProtocol);
        TheNetworkMgr->SetPortNumber(0);
        TheNetworkMgr->SetBroadcastPortNumber(PORT_NUMBER);
        PiResultNetwork::B result = TheMessageMgr->BeginMultiplayerGame(false);

        if (result != PiResultNetwork::Okay)
        {
            LOG_ERROR_TRACE("Can not begin mulitplayer game");
        }
    
        NetworkAddress address = MessageMgr::StringToAddress(REMOTE_ADDRESS);
        address.SetPort(PORT_NUMBER);
    
        result = TheMessageMgr->Connect(address);

        if (result != PiResultNetwork::Okay)
        {
            LOG_ERROR_TRACE("Can not connect to %s:%d", REMOTE_ADDRESS, PORT_NUMBER);
        }
        else
        {
            LOG_WRITE("Attempt connection to %s:%d ...", REMOTE_ADDRESS, PORT_NUMBER);
        }
    }

    if (GameState::landscapeCreated && !GameState::sendingRequestForObject)
    {
        GameState::sendingRequestForObject = true;

        LOG_WRITE("Send request for game objects");

        TheMessageMgr->SendMessage(PlayerType::Server, MessageRequestGameObjects());
    }

    {
        static uint prevTime = TheTimeMgr->GetAbsoluteTime();

        if (TheTimeMgr->GetAbsoluteTime() - prevTime >= 1000)
        {
            prevTime = TheTimeMgr->GetAbsoluteTime();

            LOG_WRITE("sended %f M, received %f M", (float)TheNetworkMgr->GetBytesSend() / (1024.0f * 1024.0f),
                                                    (float)TheNetworkMgr->GetBytesRecv() / (1024.0f * 1024.0f));
        }
    }
}


void Battler::HandleOnButtonQuit(Widget *, const WidgetEventData *)
{
    TheEngine->Quit();
}


void Battler::HandleGizmoCommand(Command *, pchar)
{

}


void Battler::HandleFogDensityCommand(Command *, pchar text)
{
    float density = Text::StringToFloat(text);

    Water::SetFogDensity(density);
}
