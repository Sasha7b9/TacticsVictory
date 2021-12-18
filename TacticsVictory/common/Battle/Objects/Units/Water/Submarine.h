// 2021/12/15 22:05:44 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Water/WaterUnit.h"
#include "Objects/Units/UnitParameters.h"


namespace Pi
{
    class Submarine : public WaterUnitObject
    {
    public:

        static Submarine *Create();

    private:

        Submarine();

        virtual ~Submarine() {};
    };


    class SubmarineController : public WaterUnitController
    {
    public:

        SubmarineController() : WaterUnitController(TypeWaterUnit::Submarine, &parameters) {}

        virtual ~SubmarineController() {}

    private:

        static UnitParameters parameters;
    };


    class CommanderSubmarine : public Commander
    {
        friend class Commander;

    public:

        virtual ~CommanderSubmarine() {}

    protected:

        CommanderSubmarine(UnitController *controller) : Commander(controller) {}

        virtual void ParseDive(const CommanderTask *) const override;
        virtual void ParseRotate(const CommanderTask *) const override;
    };


    class DriverSubmarine : public Driver
    {
        friend class Driver;

    public:

        virtual ~DriverSubmarine() {}

    protected:

        DriverSubmarine(UnitController *controller) : Driver(controller) {}
    };


    class ShooterSubmarine : public Shooter
    {
        friend class Shooter;

    public:

        virtual ~ShooterSubmarine() {}

    protected:

        ShooterSubmarine(UnitController *controller) : Shooter(controller) {}
    };
}
