﻿// 2021/12/15 21:22:39 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Ground/GroundUnit_.h"


namespace Pi
{
    class Robot : public GroundUnitObject
    {
    public:

        static GameObject *Create();

    private:

        Robot(int id = -1);

        virtual ~Robot() {};
    };


    class RobotController : public GroundUnitController
    {
    public:

        RobotController(Robot *);

        virtual ~RobotController();

        virtual void Preprocess() override;

    private:

        static const UnitParameters parameters;
    };


    class CommanderRobot : public Commander
    {
        friend class Commander;

    public:

        virtual ~CommanderRobot() {}

    protected:

        CommanderRobot(UnitController *);
    };


    class DriverRobot : public Driver
    {
        friend class Driver;

    public:

        virtual ~DriverRobot() {}

    protected:

        DriverRobot(UnitController *);
    };


    class ShooterRobot : public Shooter
    {
        friend class Shooter;

    public:

        virtual ~ShooterRobot() {}

    protected:

        ShooterRobot(UnitController *);
    };
}
