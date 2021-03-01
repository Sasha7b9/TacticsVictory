// 2021/02/26 17:28:47 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Accessories/Accessories_.h"
#include "Scene/Objects/Units/Tank/Tank_.h"
#include "Scene/Objects/Units/UnitObject/UnitObjectS.h"


void UnitObjectSpecific::RegisterObject()
{
    TheContext->RegisterFactory<UnitObjectSpecificS>();
}


void UnitObjectSpecific::CreateSpecific(Node *node)
{
    node->CreateComponent<UnitObjectSpecificS>(LOCAL);
}
