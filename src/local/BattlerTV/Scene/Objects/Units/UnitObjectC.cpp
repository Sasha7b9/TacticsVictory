// 2021/02/26 15:54:30 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/UnitObjectC.h"


void UnitObjectSpecificPart::Create(Node *node)
{
    node->CreateComponent<UnitObjectSpecificPartC>();
}
