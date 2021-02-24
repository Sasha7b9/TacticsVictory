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


void CTank::OnNodeSet(Node *node)
{
    Tank::OnNodeSet(node);

    if (node)
    {
        node_ = node;

        node_->SetName(NAME_NODE_TANK);

        LoadFromJSON(JSON_MODEL_TANK);

        Normalize();

        SharedPtr<Tile> tile(node_->CreateComponent<Tile>());

        tile->Init(node_);

        storage.Push(this);
    }
}
