// 2021/02/26 15:54:30 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/UnitsEvents_.h"
#include "Scene/Objects/Units/UnitObject_.h"
#include "Scene/Objects/Units/Accessories/Accessories_.h"
#include "Scene/Objects/Units/Ground/Tank/Tank_.h"
#include "Scene/Objects/Units/UnitObjectC.h"


UnitObjectSpecific *UnitObjectSpecific::Create(UnitObject *object)
{
    return new UnitObjectSpecificC(object);
}


UnitObjectSpecificC::UnitObjectSpecificC(UnitObject *object) : UnitObjectSpecific(object)
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
                if (t->GetNode() != node)
                {
//                    t->GetNode()->GetComponentile->Disable();
                }
                else
                {
                    int i = 0;
                    i++;
                }
            }
        }

        tile->IsEnabled() ? tile->Disable() : tile->Enable();
    }
}


void UnitObjectSpecificC::Update(float timeStep)
{
    UnitObjectSpecific::Update(timeStep);
}
