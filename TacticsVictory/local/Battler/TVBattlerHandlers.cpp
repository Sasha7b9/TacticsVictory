// 2021/12/4 22:36:23 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "TVBattler.h"
#include "Scene/World/GameWorld.h"
#include "Scene/World/Landscape_.h"


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
        TheMessageMgr->BeginMultiplayerGame(false);
    
        NetworkAddress address = MessageMgr::StringToAddress(LOCAL_ADDRESS);
        address.SetPort(PORT_NUMBER);
    
        TheMessageMgr->Connect(address);

        LOG_WRITE("Attempt connection to %s:%d ...", LOCAL_ADDRESS, PORT_NUMBER);
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
