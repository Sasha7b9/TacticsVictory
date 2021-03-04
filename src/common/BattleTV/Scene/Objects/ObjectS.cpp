// 2021/03/03 21:07:15 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/ServerS.h"
#include "Network/Game/Messages/GameMessages_.h"
#include "Scene/SceneS.h"
#include "Scene/Objects/Object_.h"
#include "Scene/Objects/ObjectS.h"



GameObjectSpecific *GameObjectSpecific::Create(GameObject *object)
{
    return new GameObjectSpecificS(object);
}


GameObjectSpecificS::GameObjectSpecificS(GameObject *object) : GameObjectSpecific(object)
{

}


void GameObjectSpecificS::Update(float)
{
    if (TheTime->GetElapsedTime() >= timeNextTimeSend)
    {
        Vector3 position = node->GetPosition();

        TheServer->SendToAll(false, Message::SendTankPosition(node->GetName(), node->GetPosition()));

        timeNextTimeSend = TheTime->GetElapsedTime() + 0.1f;
    }
}
