// 2021/12/22 10:11:26 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Messages/MessagesClient_.h"
#include "Network/Messages/MessagesServer_.h"
#include "Objects/GameObject_.h"


using namespace Pi;


bool MessageRequestGameObjects::HandleMessage(Player *sender) const
{
    LOG_WRITE("Received a request to send objects. In scene %d objects", GameObject::objects.GetElementCount());

    for (GameObject *object : GameObject::objects)
    {
        TheMessageMgr->SendMessage(sender->GetPlayerKey(), MessageCreateGameObject(object));
    }

    return true;
}
