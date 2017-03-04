#pragma once
#include "Game/Objects/Buildings/BuildingObject.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MilitaryPlant : public BuildingObject
{
public:
    MilitaryPlant(Context *context = gContext);

    static void RegisterObject(Context *context = gContext);

    static SharedPtr<MilitaryPlant> Create();

private:
    void Init();
    void LoadFromFile();

    DEFAULT_MEMBERS(MilitaryPlant);
};
