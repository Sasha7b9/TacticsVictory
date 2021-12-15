// 2021/12/15 21:22:39 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Ground/GroundUnit.h"


namespace Pi
{
    class Robot : public GroundUnitObject
    {
    public:

        static GameObject *Create();

    private:

        Robot() : GroundUnitObject(TTypeGroundUnit::Robot) {};
        virtual ~Robot() {};
    };


    class RobotController : public GroundUnitController
    {
    public:

        RobotController();
        virtual ~RobotController();

        virtual void Preprocess() override;

    private:

        RobotController(const RobotController &);

        virtual Controller *Replicate() const override;
    };
}
