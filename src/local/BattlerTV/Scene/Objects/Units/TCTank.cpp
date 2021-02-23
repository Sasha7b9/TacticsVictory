// 2021/02/22 15:40:32 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#include "stdafx.h"
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


SharedPtr<CTank> CTank::Create(uint row, uint col)
{
    SharedPtr<CTank> tank(TheScene->CreateChild("CTank", LOCAL)->CreateComponent<CTank>(LOCAL));

    tank->LoadFromJSON("Models/Tank.json");

    tank->Normalize();

    tank->SetPosition({ (float)row, 0, -(float)col });

    storage.Push(tank);

    return tank;
}


void CTank::FixedUpdate(float /*time*/)
{

}
