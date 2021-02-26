// 2021/02/26 17:28:47 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/UnitObject/UnitObjectS.h"


void UnitObjectSpecific::Create(Node *node)
{
    node->CreateComponent<UnitObjectSpecificS>();
}
