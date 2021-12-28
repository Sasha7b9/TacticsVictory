// 2021/12/21 17:55:23 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Messages/MessagesClient_.h"
#include "Objects/GameObject_.h"
#include "Utils/PeriodicTask_.h"
#include "PeriodicTasks.h"
#include "Network/Messages/MessagesServer_.h"


using namespace Pi;


uint MessagePing::time_prev = 0;


MessagePing::MessagePing() :
    Message(PiTypeMessage::Ping, PiFlagMessage::Unordered)
#ifdef PiCLIENT
    ,
    timeSend(TheTimeMgr->GetMillisecondCount())
#endif
{
#ifdef PiCLIENT
    if (time_prev != 0)
    {
        if (timeSend > time_prev + 10000)
        {
            LOG_WRITE("Server lost ...");
            time_prev = 0;
            ListPeriodicTask::Self()->Append(TaskConnecting::Self(), 1000);
        }
    }
#endif
}


void MessagePing::Compress(Compressor &data) const
{
    data << timeSend;
}


bool MessagePing::Decompress(Decompressor &data)
{
    data >> timeSend;

    return true;
}


bool MessagePing::HandleMessage(Player *sender) const
{
#ifdef PiCLIENT

    if (TaskPing::Self()->EnabledLogging())
    {
        LOG_WRITE("ping = %d ms", TheTimeMgr->GetMillisecondCount() - timeSend);
    }

    time_prev = TheTimeMgr->GetMillisecondCount();

#else

    TheMessageMgr->SendMessage(sender->GetPlayerKey(), *this);

#endif

    return true;
}


void MessageRequestCreateGameObject::Compress(Compressor &data) const
{
    data << id;
}


bool MessageRequestCreateGameObject::Decompress(Decompressor &data)
{
    data >> id;

    return true;
}


bool MessageRequestCreateGameObject::HandleMessage(Player *sender) const
{
#ifdef PiSERVER

    GameObject *object = GameObject::objects.Find(id);

    if (object)
    {
        MessageCreateGameObject message(object);
        message.SetMessageFlags(PiFlagMessage::Unordered | PiFlagMessage::Unreliable);

        TheMessageMgr->SendMessage(sender->GetPlayerKey(), message);
    }

#endif

    return true;
}
