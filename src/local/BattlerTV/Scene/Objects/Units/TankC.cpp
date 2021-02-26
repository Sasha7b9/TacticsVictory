// 2021/02/25 21:40:14 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Tank_.h"
#include "Scene/Objects/Units/TankC.h"
#include "Scene/Objects/Units/UnitObjectC.h"


void Tank::RegisterObject()
{
    TheContext->RegisterFactory<Tank>();
    TheContext->RegisterFactory<TankSpecificPartC>();
    TheContext->RegisterFactory<UnitObjectSpecificPartC>();
}


void TankSpecificPart::Create(Node *node)
{
    node->CreateComponent<TankSpecificPartC>();
}
