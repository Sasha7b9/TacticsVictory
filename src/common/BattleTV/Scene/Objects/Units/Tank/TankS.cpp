// 2021/02/25 22:10:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/ServerS.h"
#include "Network/Game/Messages/GameMessages_.h"
#include "Scene/Objects/Units/Tank/Tank_.h"
#include "Scene/Objects/Units/Tank/TankS.h"
#include "Scene/Objects/Units/UnitObject/UnitObjectS.h"


void Tank::RegisterObject()
{
    TheContext->RegisterFactory<Tank>();
    TheContext->RegisterFactory<TankSpecificS>();
}


void Tank::Update(float timeStep)
{
    UnitObject::Update(timeStep);

    if (TheTime->GetElapsedTime() >= GetComponent<TankSpecificS>()->timeNextTimeSend)
    {
        TheServer->SendToAll(false, Message::SendTankPosition(node_->GetName(), node_->GetPosition()));

        GetComponent<TankSpecificS>()->timeNextTimeSend = TheTime->GetElapsedTime() + 0.1f;
    }
}


void TankSpecific::CreateSpecific(Node *node)
{
    node->CreateComponent<TankSpecificS>(LOCAL);
}


void TankSpecificS::Update(float /*timeStep*/)
{

}
