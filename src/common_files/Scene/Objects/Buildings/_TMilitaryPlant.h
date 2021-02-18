/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "Scene/Objects/Buildings/_TBuildingObject.h"


class MilitaryPlant : public BuildingObject
{
public:
    MilitaryPlant(Context *context = TheContext);

    static void RegisterObject(Context *context = TheContext);

    virtual void Update(float timeStep) override { UNUSED(timeStep); }

    static SharedPtr<MilitaryPlant> Create();

private:
    void Init();
    void LoadFromFile();
};
