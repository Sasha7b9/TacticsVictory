// 2021/12/15 22:05:44 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Water/WaterUnit.h"


namespace Pi
{
    class Submarine : public WaterUnitObject
    {
    public:

        static GameObject *Create();

    private:

        Submarine() : WaterUnitObject(TTypeWaterUnit::Submarine) {};
        virtual ~Submarine() {};
    };


    class SubmarineController : public WaterUnitController
    {
    public:

        SubmarineController();
        virtual ~SubmarineController();

        virtual void Preprocess() override;

    private:

        SubmarineController(const SubmarineController &);

        virtual Controller *Replicate() const override;
    };
}
