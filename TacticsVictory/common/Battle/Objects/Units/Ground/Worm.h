// 2021/12/15 21:29:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Ground/GroundUnit.h"


namespace Pi
{
    class Worm : public GroundUnitObject
    {
    public:

        static GameObject *Create();

    private:

        Worm() : GroundUnitObject(TTypeGroundUnit::Worm) {};
        virtual ~Worm() {};
    };


    class WormController : public GroundUnitController
    {
    public:

        WormController();
        virtual ~WormController();

        virtual void Preprocess() override;

    private:

        WormController(const WormController &);

        virtual Controller *Replicate() const override;
    };
}
