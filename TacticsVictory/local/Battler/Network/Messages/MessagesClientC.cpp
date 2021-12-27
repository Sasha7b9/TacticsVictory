// 2021/12/22 9:29:47 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Messages/MessagesClient_.h"
#include "PeriodicTasks.h"


using namespace Pi;


MessagePing::MessagePing() :
    Message(PiTypeMessage::Ping, PiFlagMessage::Unordered),
    timeSend(TheTimeMgr->GetMillisecondCount())
{
    if (time_prev != 0)
    {
        if (timeSend > time_prev + 10000)
        {
            LOG_WRITE("Server lost ...");
            time_prev = 0;
            ListPeriodicTask::Self()->Append(TaskConnecting::Self(), 1000);
        }
    }
}


bool MessagePing::HandleMessage(Player *) const
{
    if(TaskPing::Self()->EnabledLogging())
    {
        LOG_WRITE("ping = %d ms", TheTimeMgr->GetMillisecondCount() - timeSend);
    }

    time_prev = TheTimeMgr->GetMillisecondCount();

    return true;
}


bool MessageRequestCreateGameObject::HandleMessage(Player *) const
{
    return true;
}

