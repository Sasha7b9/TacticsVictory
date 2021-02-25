// 2021/02/25 21:45:21 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Tank_.h"
#include "Scene/Objects/Units/TankSpecificPartC.h"
#include "Scene/Objects/Units/UnitsEvents_.h"


void TankSpecificPartC::Start(Node *node)
{
    tile = node->CreateComponent<Tile>();
}


void TankSpecificPartC::OnMouseClick(VariantMap &eventData, Node *node)
{
    using namespace UnitMouseClick;

    if (eventData[P_NODE].GetPtr() == node)
    {
        if (!eventData[P_CTRL_PRESSED].GetBool())
        {
            for (Tank *tank : Tank::storage)
            {
                TankSpecificPartC *sp = (TankSpecificPartC *)(tank->specific.Get());

                sp->tile->Disable();
            }
        }

        tile->IsEnabled() ? tile->Disable() : tile->Enable();
    }
}
