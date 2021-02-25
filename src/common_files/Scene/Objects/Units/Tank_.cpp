// 2021/02/22 15:40:32 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#include "stdafx.h"
#include "Graphics/3D/TTile.h"
#include "Scene/SceneC.h"
#include "Scene/Objects/Units/Tank_.h"
#include "Scene/Objects/Units/UnitsEvents_.h"


Vector<Tank *> Tank::storage;


Tank::Tank(Context *context) : UnitObject(context)
{

}


void Tank::RegisterObject()
{
    TheContext->RegisterFactory<Tank>();
}


void Tank::FixedUpdate(float /*time*/)
{

}


void Tank::Start()
{
    UnitObject::Start();

    LoadFromJSON(JSON_MODEL_TANK);

    Normalize();

    tile = node_->CreateComponent<Tile>();

    storage.Push(this);

    SubscribeToEvent(EU_MOUSE_CLICK, URHO3D_HANDLER(Tank, HandleMouseClick));
}


void Tank::OnNodeSet(Node *node)
{
    if (node)
    {
        node_ = node->CreateChild(NAME_NODE_TANK);
    }

    UnitObject::OnNodeSet(node ? node_ : node);
}


void Tank::HandleMouseClick(StringHash, VariantMap &eventData)
{
    using namespace UnitMouseClick;

    if (eventData[P_NODE].GetPtr() == node_)
    {
        if (!eventData[P_CTRL_PRESSED].GetBool())
        {
            for (Tank *tank : Tank::storage)
            {
                tank->tile->Disable();
            }
        }

        tile->IsEnabled() ? tile->Disable() : tile->Enable();
    }
}
