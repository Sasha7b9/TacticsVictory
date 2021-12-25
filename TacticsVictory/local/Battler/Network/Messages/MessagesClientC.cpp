// 2021/12/22 9:29:47 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Messages/MessagesClient_.h"


using namespace Pi;


MessagePing::MessagePing() :
    Message(PiTypeMessage::Ping, PiFlagMessage::Unordered),
    timeSend(TheTimeMgr->GetMillisecondCount())
{
}


bool MessagePing::HandleMessage(Player *) const
{
    LOG_WRITE("ping = %d ms", TheTimeMgr->GetMillisecondCount() - timeSend);

    return true;
}


bool MessageRequestCreateGameObject::HandleMessage(Player *) const
{
    return true;
}

