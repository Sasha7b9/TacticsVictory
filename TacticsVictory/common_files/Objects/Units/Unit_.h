// 2021/12/1 9:47:27 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/GameObject_.h"
#include "Objects/Staff/Driver_.h"
#include "Objects/Staff/Shooter_.h"
#include "Objects/GameObjectParameters_.h"
#include "Objects/Staff/CommanderTasks_.h"


namespace Pi
{
    class AirUnitObject;
    class GroundUnitObject;
    class WaterUnitObject;


    class UnitObject : public GameObject, public MapElement<UnitObject>
    {
    public:

        static void Construct();
        static void Destruct();

        const TypeUnit typeUnit;

        static Map<UnitObject> objects;

        AirUnitObject *GetAirUnit() { return typeUnit == TypeUnit::Air ? (AirUnitObject *)this : nullptr; }
        GroundUnitObject *GetGroundUnit() { return typeUnit == TypeUnit::Ground ? (GroundUnitObject *)this : nullptr; }
        WaterUnitObject *GetWaterUnit() { return typeUnit == TypeUnit::Water ? (WaterUnitObject *)this : nullptr; }

        virtual void Move(float dT) override;

    protected:

        UnitObject(TypeUnit, const GameObjectParameters *, int);
    };
}
