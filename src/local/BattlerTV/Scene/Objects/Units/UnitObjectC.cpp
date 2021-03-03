// 2021/02/26 15:54:30 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/UnitsEvents_.h"
#include "Scene/Objects/Units/UnitObject_.h"
#include "Scene/Objects/Units/Accessories/Accessories_.h"
#include "Scene/Objects/Units/Ground/Tank/Tank_.h"
#include "Scene/Objects/Units/UnitObjectC.h"


GameObjectSpecific *UnitObjectSpecific::Create(UnitObject *object)
{
    return new UnitObjectSpecificC(object);
}


void UnitObjectSpecificC::Update(float timeStep)
{
    GameObjectSpecificC::Update(timeStep);
}


UnitObjectSpecificC::UnitObjectSpecificC(UnitObject *object) : GameObjectSpecificC(object)
{
    tile = object->GetNode()->CreateComponent<TileSelected>(LOCAL);

    SubscribeToEvent(EU_MOUSE_CLICK, URHO3D_HANDLER(UnitObjectSpecificC, HandleMouseClick));
}


void UnitObjectSpecificC::HandleMouseClick(StringHash, VariantMap &eventData)
{
    using namespace UnitMouseClick;

    if (eventData[P_NODE].GetPtr() == node)
    {
        if (!eventData[P_CTRL_PRESSED].GetBool())
        {
            for (Tank *t : Tank::storage)
            {
                t->GetNode()->GetComponent<TileSelected>()->Disable();
            }
        }

        tile->IsEnabled() ? tile->Disable() : tile->Enable();
    }
}
