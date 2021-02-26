// 2021/02/25 22:10:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Tank_.h"
#include "Scene/Objects/Units/TankS.h"
#include "Scene/Objects/Units/UnitObjectS.h"


void TankSpecificPart::Create(Node *node)
{
    node->CreateComponent<TankSpecificPartS>();
}
