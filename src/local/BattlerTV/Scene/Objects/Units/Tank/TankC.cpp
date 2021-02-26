// 2021/02/25 21:40:14 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Tank/Tank_.h"
#include "Scene/Objects/Units/Tank/TankC.h"
#include "Scene/Objects/Units/UnitObject/UnitObjectC.h"


void Tank::RegisterObject()
{
    TheContext->RegisterFactory<Tank>();
    TheContext->RegisterFactory<TankSpecificPartC>();
    TheContext->RegisterFactory<UnitObjectSpecificC>();
}


void TankSpecificPart::Create(Node *node)
{
    node->CreateComponent<TankSpecificPartC>();
}
