/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "Scene/Objects/Buildings/BuildingObject.h"



class MilitaryPlant : public BuildingObject
{
public:
    MilitaryPlant(Context *context = TheContext);

    static void RegisterObject(Context *context = TheContext);

    static SharedPtr<MilitaryPlant> Create();

private:
    void Init();
    void LoadFromFile();

    DEFAULT_MEMBERS(MilitaryPlant);
};
