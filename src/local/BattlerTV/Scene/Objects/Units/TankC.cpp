// 2021/02/25 21:40:14 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Tank_.h"
#include "Scene/Objects/Units/TankC.h"
#include "Scene/Objects/Units/UnitsEvents_.h"
#include "Scene/Objects/Units/UnitObjectC.h"


Tank::Tank(Context *) : UnitObject(new UnitObjectSpecificPartC())
{
    specific = new TankSpecificPartC();
}


void TankSpecificPartC::HandleMouseClick(StringHash, VariantMap &eventData)
{
    using namespace UnitMouseClick;

    if (eventData[P_NODE].GetPtr() == tank->node_)
    {
        if (!eventData[P_CTRL_PRESSED].GetBool())
        {
            for (Tank *t : Tank::storage)
            {
                if (t != tank)
                {
                    TankSpecificPartC *sp = (TankSpecificPartC *)(t->specific.Get());

                    sp->tile->Disable();
                }
            }
        }

        tile->IsEnabled() ? tile->Disable() : tile->Enable();
    }
}

void TankSpecificPartC::Start(Tank *_tank)
{
    TankSpecificPart::Start(_tank);

    tile = tank->node_->CreateComponent<TileSelected>();

    SubscribeToEvent(EU_MOUSE_CLICK, URHO3D_HANDLER(TankSpecificPartC, HandleMouseClick));
}
