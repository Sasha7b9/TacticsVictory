// 2021/02/22 15:40:32 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#include "stdafx.h"
#include "Graphics/3D/TTile.h"
#include "Scene/TCScene.h"
#include "Scene/Objects/Units/TCTank.h"


Vector<CTank *> CTank::storage;


CTank::CTank(Context *context) : Tank(context)
{

}


void CTank::RegisterObject()
{
    TheContext->RegisterFactory<CTank>();
}


void CTank::FixedUpdate(float /*time*/)
{

}


void CTank::Start()
{
    Tank::Start();

    LoadFromJSON(JSON_MODEL_TANK);

    Normalize();

    tile = node_->CreateComponent<Tile>();

    storage.Push(this);
}


void CTank::OnNodeSet(Node *node)
{
    if (node)
    {
        node_ = node->CreateChild(NAME_NODE_TANK);
    }

    Tank::OnNodeSet(node ? node_ : node);
}
