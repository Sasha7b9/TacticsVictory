// 2021/02/25 21:40:14 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Tank_.h"
#include "Scene/Objects/Units/TankC.h"
#include "Scene/Objects/Units/UnitsEvents_.h"


Tank::Tank(Context *context) : UnitObject(context)
{
    specific = new TankSpecificPartC();
}


void Tank::HandleMouseClick(StringHash, VariantMap &eventData)
{
    specific->OnMouseClick(eventData);
}

void TankSpecificPartC::Start(Node *_node, Tank *_tank)
{
    TankSpecificPart::Start(_node, _tank);

    tile = node->CreateComponent<Tile>();
}


void TankSpecificPartC::OnMouseClick(VariantMap &eventData)
{
    using namespace UnitMouseClick;

    if (eventData[P_NODE].GetPtr() == node)
    {
        if (!eventData[P_CTRL_PRESSED].GetBool())
        {
            for (Tank *t : Tank::storage)
            {
                TankSpecificPartC *sp = (TankSpecificPartC *)(t->specific.Get());

                sp->tile->Disable();
            }
        }

        tile->IsEnabled() ? tile->Disable() : tile->Enable();
    }
}