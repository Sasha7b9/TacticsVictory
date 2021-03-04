// 2021/02/26 15:54:30 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/UnitsEvents_.h"
#include "Scene/Objects/Units/Unit_.h"
#include "Scene/Objects/Units/Accessories/Accessories_.h"
#include "Scene/Objects/Units/Ground/Tank/Tank_.h"
#include "Scene/Objects/Units/UnitC.h"


void UnitSpecificC::Update(float timeStep)
{
    ObjectSpecificC::Update(timeStep);
}


UnitSpecificC::UnitSpecificC(Unit *object) : ObjectSpecificC(object)
{
    tile = object->GetNode()->CreateComponent<TileSelected>(LOCAL);

    SubscribeToEvent(EU_MOUSE_CLICK, URHO3D_HANDLER(UnitSpecificC, HandleMouseClick));
}


void UnitSpecificC::HandleMouseClick(StringHash, VariantMap &eventData)
{
    using namespace UnitMouseClick;

    if (eventData[P_NODE].GetPtr() == node)
    {
        if (!eventData[P_CTRL_PRESSED].GetBool())
        {
            for (Unit *o : Unit::storage)
            {
                o->GetNode()->GetComponent<TileSelected>()->Disable();
            }
        }

        tile->IsEnabled() ? tile->Disable() : tile->Enable();
    }
}
