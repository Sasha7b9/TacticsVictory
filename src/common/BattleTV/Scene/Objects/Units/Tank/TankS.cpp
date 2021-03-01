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


void TankSpecific::CreateSpecific(Node *node)
{
    node->CreateComponent<TankSpecificS>(LOCAL);
}


void Tank::Update(float timeStep)
{
    EngineT *engine = GetComponent<EngineT>();

    engine->Update(timeStep);

    if (engine->algorithm.IsFinished())
    {
        int direct = Rand() % 4;

        engine->GiveCommand((CommandEngine::E)(direct + 1));
    }

    TheServer->SendToAll(Message::SendTankPosition(GetID(), node_->GetPosition()));
}
