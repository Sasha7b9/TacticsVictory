// 2021/12/15 21:37:23 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Water/WaterUnit_.h"


namespace Pi
{
    class Boat : public WaterUnitObject
    {
    public:

        static GameObject *Create();

    private:

        Boat() : WaterUnitObject(TypeWaterUnit::Boat) {};
        virtual ~Boat() {};
    };


    class BoatController : public WaterUnitController
    {
    public:

        BoatController();
        virtual ~BoatController();

        virtual void Preprocess() override;

    private:

        static const UnitParameters parameters;

        BoatController(const BoatController &);

        BoatController &operator=(const BoatController &rhs) { *this = rhs; return *this; }

        virtual Controller *Replicate() const override;
    };


    class CommanderBoat : public Commander
    {
        friend class Commander;

    public:

        virtual ~CommanderBoat() {}

    protected:

        CommanderBoat(UnitController *);
    };


    class DriverBoat : public Driver
    {
        friend class Driver;

    public:

        virtual ~DriverBoat() {}

    protected:

        DriverBoat(UnitController *);
    };


    class ShooterBoat : public Shooter
    {
        friend class Shooter;

    public:

        virtual ~ShooterBoat() {}

    protected:

        ShooterBoat(UnitController *);
    };
}
