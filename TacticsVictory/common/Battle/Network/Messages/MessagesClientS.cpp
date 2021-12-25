// 2021/12/22 10:11:26 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Messages/MessagesClient_.h"
#include "Network/Messages/MessagesServer_.h"
#include "Objects/GameObject_.h"


using namespace Pi;


MessagePing::MessagePing() :
    Message(PiTypeMessage::Ping)
{
}


bool MessagePing::HandleMessage(Player *sender) const
{
    TheMessageMgr->SendMessage(sender->GetPlayerKey(), *this);

    return true;
}


bool MessageRequestCreateGameObject::HandleMessage(Player *sender) const
{
    GameObject *object = GameObject::objects.Find(id);

    if(object)
    {
        MessageCreateGameObject message(object);
        message.SetMessageFlags(PiFlagMessage::Unordered | PiFlagMessage::Unreliable);

        TheMessageMgr->SendMessage(sender->GetPlayerKey(), message);
    }

    return true;
}
