// 2021/12/15 21:29:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Ground/GroundUnit_.h"


namespace Pi
{
    class Worm : public GroundUnitObject
    {
    public:

        static GameObject *Create();

    private:

        Worm() : GroundUnitObject(TypeGroundUnit::Worm) {};
        virtual ~Worm() {};
    };


    class WormController : public GroundUnitController
    {
    public:

        WormController();

        virtual ~WormController();

        virtual void Preprocess() override;

    private:

        static UnitParameters parameters;

        WormController(const WormController &);

        WormController &operator=(const WormController &) { return *this; }

        virtual Controller *Replicate() const override;
    };


    class CommanderWorm : public Commander
    {
        friend class Commander;

    public:

        virtual ~CommanderWorm() {}

    protected:

        CommanderWorm(UnitController *);
    };


    class DriverWorm : public Driver
    {
        friend class Driver;

    public:

        virtual ~DriverWorm() {}

    protected:

        DriverWorm(UnitController *);
    };


    class ShooterWorm : public Shooter
    {
        friend class Shooter;

    public:

        virtual ~ShooterWorm() {}

    protected:

        ShooterWorm(UnitController *);
    };
}
