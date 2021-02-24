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


SharedPtr<CTank> CTank::Create(int z, int x)
{
    SharedPtr<CTank> tank(TheScene->CreateChild(NAME_NODE_TANK, LOCAL)->CreateComponent<CTank>(LOCAL));

    tank->LoadFromJSON(JSON_MODEL_TANK);

    tank->Normalize();

    tank->SetPosition({ (float)x, 0, (float)z });

    SharedPtr<Tile> tile(new Tile(TheScene, "select"));

    storage.Push(tank);

    return tank;
}


void CTank::FixedUpdate(float /*time*/)
{

}
