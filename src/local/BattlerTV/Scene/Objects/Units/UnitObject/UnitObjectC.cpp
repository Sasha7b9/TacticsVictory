// 2021/02/26 15:54:30 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/UnitsEvents_.h"
#include "Scene/Objects/Units/Tank/Tank_.h"
#include "Scene/Objects/Units/UnitObject/UnitObjectC.h"


void UnitObject::RegisterObject()
{
    TheContext->RegisterFactory<UnitObjectSpecificC>();
    TheContext->RegisterFactory<Engine>();

    Tank::RegisterObject();
}


void UnitObjectSpecific::CreateSpecific(Node *node)
{
    node->CreateComponent<UnitObjectSpecificC>(LOCAL);
}


void UnitObjectSpecificC::HandleMouseClick(StringHash, VariantMap &eventData)
{
    using namespace UnitMouseClick;

    if (eventData[P_NODE].GetPtr() == node_)
    {
        if (!eventData[P_CTRL_PRESSED].GetBool())
        {
            for (Tank *t : Tank::storage)
            {
                if (t->GetNode() != node_)
                {
                    t->GetNode()->GetComponent<UnitObjectSpecificC>()->tile->Disable();
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


void UnitObjectSpecificC::OnNodeSet(Node *node)
{
    if (node)
    {
        UnitObjectSpecific::OnNodeSet(node);

        tile = node->CreateComponent<TileSelected>(LOCAL);

        SubscribeToEvent(EU_MOUSE_CLICK, URHO3D_HANDLER(UnitObjectSpecificC, HandleMouseClick));
    }
}
