// 2021/12/15 21:37:23 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Water/WaterUnit.h"


namespace Pi
{
    class Boat : public WaterUnitObject
    {
    public:

        static GameObject *Create();

    private:

        Boat() : WaterUnitObject(TTypeWaterUnit::Boat) {};
        virtual ~Boat() {};
    };


    class BoatController : public WaterUnitController
    {
    public:

        BoatController();
        virtual ~BoatController();

        virtual void Preprocess() override;

    private:

        BoatController(const BoatController &);

        virtual Controller *Replicate() const override;
    };
}
