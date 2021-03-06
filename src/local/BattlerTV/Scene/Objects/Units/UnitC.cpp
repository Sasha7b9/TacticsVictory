// 2021/02/26 15:54:30 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/UnitsEvents_.h"
#include "Scene/Objects/Units/Unit_.h"
#include "Scene/Objects/Units/Ground/Tank/Tank_.h"
#include "Scene/Objects/Units/UnitC.h"


void UnitSpecificC::Update(float timeStep)
{
    ObjectSpecificC::Update(timeStep);
}


UnitSpecificC::UnitSpecificC(Unit *object) : ObjectSpecificC(object)
{
    tile = object->GetObjectNode()->CreateComponent<TileSelected>(LOCAL);

    if (tile == nullptr)
    {
        tile = tile;
    }

    SubscribeToEvent(EU_MOUSE_CLICK, URHO3D_HANDLER(UnitSpecificC, HandleMouseClick));
}


void UnitSpecificC::HandleMouseClick(StringHash, VariantMap &eventData)
{
    using namespace UnitMouseClick;

    if (eventData[P_NODE].GetPtr() == object->GetObjectNode())
    {
        if (!eventData[P_CTRL_PRESSED].GetBool())
        {
            RandomAccessIterator<Unit *> it = Unit::storage.Begin();

            while (it != Unit::storage.End())
            {
                (*it)->GetObjectNode()->GetComponent<TileSelected>()->Disable();

                it++;
            }
        }

        tile->IsEnabled() ? tile->Disable() : tile->Enable();
    }
}
