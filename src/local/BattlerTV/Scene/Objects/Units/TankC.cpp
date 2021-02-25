// 2021/02/25 21:40:14 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Tank_.h"
#include "Scene/Objects/Units/TankSpecificPartC.h"


Tank::Tank(Context *context) : UnitObject(context)
{
    specific = new TankSpecificPartC();
}


void Tank::HandleMouseClick(StringHash, VariantMap &eventData)
{
    specific->OnMouseClick(eventData, node_);
}
