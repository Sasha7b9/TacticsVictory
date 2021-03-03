// 2021/02/25 22:10:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/ServerS.h"
#include "Network/Game/Messages/GameMessages_.h"
#include "Scene/Objects/Units/Ground/Tank/Tank_.h"
#include "Scene/Objects/Units/Ground/Tank/TankS.h"
#include "Scene/Objects/Units/UnitObjectS.h"


void Tank::RegisterObject()
{
    TheContext->RegisterFactory<Tank>();
    TheContext->RegisterFactory<TankSpecificS>();
}


void Tank::Update(float timeStep)
{
    UnitObject::Update(timeStep);

    static Node *node = nullptr;

    if (TheTime->GetElapsedTime() >= GetComponent<TankSpecificS>()->timeNextTimeSend)
    {
        if (node == nullptr)
        {
            node = node_;
        }

        Vector3 position = node_->GetPosition();

        TheServer->SendToAll(false, Message::SendTankPosition(node_->GetName(), node_->GetPosition()));

        GetComponent<TankSpecificS>()->timeNextTimeSend = TheTime->GetElapsedTime() + 0.1f;

        if (node_ == node)
        {
            node = node;
        }
    }
}


void TankSpecific::Create(Node *node)
{
    node->CreateComponent<TankSpecificS>(LOCAL);
}


void TankSpecificS::Update(float /*timeStep*/)
{

}
