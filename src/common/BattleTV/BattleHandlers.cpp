// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Battle.h"
#include "Network/Game/Messages/GameMessages_.h"
#include "Scene/Scene_.h"


void Battle::HandleUpdate(StringHash, VariantMap& /*eventData*/)
{
//    float time = eventData[Update::P_TIMESTEP].GetFloat();
}


void Battle::HandlePostUpdate(StringHash, VariantMap& /*eventData*/)
{
//    static uint prevSend = 0;
//
//    if (TheTime->GetSystemTime() - prevSend > 1000)
//    {
//        uint start = TheTime->GetSystemTime();
//
//        TheServer->SendToAll(true, Message::SendScene());
//
//        LOGINFOF("Time send scene %d ms", TheTime->GetSystemTime() - start);
//
//        prevSend = TheTime->GetSystemTime();
//    }
}
