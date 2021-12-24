// 2021/12/4 22:36:23 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "TVBattler.h"
#include "Scene/World/GameWorld.h"
#include "Scene/World/Landscape_.h"
#include "Network/Messages/MessagesClient_.h"
#include "GameState.h"
#include "Objects/GameObject_.h"


using namespace Pi;


void Battler::ApplicationTask()
{
    if (GameState::landscapeCreated && !GameState::sendingRequestForObject)
    {
        GameState::sendingRequestForObject = true;

        LOG_WRITE("Send request for game objects");

        TheMessageMgr->SendMessage(PlayerType::Server, MessageRequestGameObjects());
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


void Battler::HandlePingCommand(Command *, pchar text)
{
    TheMessageMgr->SendMessage(PlayerType::Server, MessagePing(TheTimeMgr->GetMillisecondCount()));
}
