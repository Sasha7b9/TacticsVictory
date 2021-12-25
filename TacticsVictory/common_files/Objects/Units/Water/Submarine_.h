// 2021/12/15 22:05:44 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Water/WaterUnit_.h"
#include "Objects/Units/UnitParameters_.h"


namespace Pi
{
    class Submarine : public WaterUnitObject, public MapElement<Submarine>
    {
    public:

        static Submarine *Create(int id = -1);

        static Map<Submarine> objects;

    private:

        Submarine(int id = -1);

        virtual ~Submarine() {};
    };


    class SubmarineController : public WaterUnitController
    {
    public:

        SubmarineController(Submarine *);

        virtual ~SubmarineController() {}

    private:

        static const UnitParameters parameters;
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
