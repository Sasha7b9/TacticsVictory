// 2021/02/25 22:10:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Tank/Tank_.h"
#include "Scene/Objects/Units/Tank/TankS.h"
#include "Scene/Objects/Units/UnitObject/UnitObjectS.h"


void Tank::RegisterObject()
{
    TheContext->RegisterFactory<Tank>();
    TheContext->RegisterFactory<TankSpecific>();
}


void TankSpecific::CreateSpecific(Node *node)
{
    node->CreateComponent<TankSpecificS>();
}
