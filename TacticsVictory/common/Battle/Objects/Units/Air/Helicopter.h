// 2021/12/15 21:15:28 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Air/AirUnit.h"


namespace Pi
{
    class Helicopter : public AirUnitObject
    {
    public:

        static GameObject *Create();

    private:

        Helicopter() : AirUnitObject(TTypeAirUnit::Helicopter) {};
        virtual ~Helicopter() {};
    };


    class HelicopterController final : public AirUnitController
    {
    public:

        HelicopterController();
        ~HelicopterController();

        virtual void Preprocess() override;

    private:

        HelicopterController(const HelicopterController &);

        virtual Controller *Replicate() const override;
    };
}
