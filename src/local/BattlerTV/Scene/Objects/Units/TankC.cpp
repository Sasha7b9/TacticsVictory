// 2021/02/25 21:40:14 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Tank_.h"
#include "Scene/Objects/Units/TankC.h"
#include "Scene/Objects/Units/UnitsEvents_.h"
#include "Scene/Objects/Units/UnitObjectC.h"


Tank::Tank(Context *) : UnitObject(new UnitObjectSpecificPartC())
{

}


void Tank::RegisterObject()
{
    TheContext->RegisterFactory<Tank>();
    TheContext->RegisterFactory<TankSpecificPartC>();
}


void TankSpecificPartC::HandleMouseClick(StringHash, VariantMap &eventData)
{
    using namespace UnitMouseClick;

    if (eventData[P_NODE].GetPtr() == node_)
    {
        if (!eventData[P_CTRL_PRESSED].GetBool())
        {
            for (Tank *t : Tank::storage)
            {
                if (t->node_ != node_)
                {
                    t->node_->GetComponent<TankSpecificPartC>()->tile->Disable();
                }
            }
        }

        tile->IsEnabled() ? tile->Disable() : tile->Enable();
    }
}


void TankSpecificPartC::OnNodeSet(Node *node)
{
    if (node)
    {
        TankSpecificPart::OnNodeSet(node);

        tile = node->CreateComponent<TileSelected>();

        SubscribeToEvent(EU_MOUSE_CLICK, URHO3D_HANDLER(TankSpecificPartC, HandleMouseClick));
    }
}


void TankSpecificPart::Create(Node *node)
{
    node->CreateComponent<TankSpecificPartC>();
}
