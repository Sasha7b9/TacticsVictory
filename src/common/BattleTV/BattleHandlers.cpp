// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Battle.h"
#include "Network/Game/Messages/GameMessages_.h"
#include "Scene/Scene_.h"


void Battle::HandleUpdate(StringHash, VariantMap& eventData)
{
    float dT = eventData[Update::P_TIMESTEP].GetFloat();

    LOGINFOF("dT = %f ms", dT);
}


void Battle::HandlePostUpdate(StringHash, VariantMap& /*eventData*/)
{
    static uint prevSend = 0;

    if (TheTime->GetSystemTime() - prevSend > 30)
    {
        TheServer->SendToAll(true, Message::SendScene());

        prevSend = TheTime->GetSystemTime();
    }
}
