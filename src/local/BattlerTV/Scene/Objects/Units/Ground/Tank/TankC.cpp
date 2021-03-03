// 2021/02/25 21:40:14 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Ground/Tank/Tank_.h"
#include "Scene/Objects/Units/Ground/Tank/TankC.h"
#include "Scene/Objects/Units/UnitObjectC.h"


void Tank::RegisterObject()
{
    TheContext->RegisterFactory<Tank>();
    TheContext->RegisterFactory<TankSpecificC>();
}


void TankSpecific::Create(Node *node)
{
    node->CreateComponent<TankSpecificC>(LOCAL);
}


void Tank::Update(float)
{

}
