// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Ground/GroundUnit_.h"


namespace Pi
{
    class TankController;


    class Tank : public GroundUnitObject, public MapElement<Tank>
    {
    public:

        static Tank *Create(int id = -1);

        static Map<Tank> objects;

    private:

        Tank(int id = -1);
        virtual ~Tank() {};

        Node *CreateBody();
        Node *CreateTrack(bool left);
        Node *CreateTower();
        Node *CreateBarrel();
    };


    class TankController : public GroundUnitController
    {
    public:

        TankController(Tank *);

        virtual ~TankController();

        virtual void Preprocess() override;

    private:

        static const UnitParameters parameters;
    };


    class CommanderTank : public Commander
    {
        friend class Commander;

    public:

        virtual ~CommanderTank() {}

    protected:

        CommanderTank(UnitController *);

    private:

        virtual void ParseMove(const CommanderTask *task) const override;
    };


    class DriverTank : public Driver
    {
        friend class Driver;

    public:

        virtual ~DriverTank() {}

    protected:

        DriverTank(UnitController *);
    };


    class ShooterTank : public Shooter
    {
        friend class Shooter;

    public:

        virtual ~ShooterTank() {}

    protected:

        ShooterTank(UnitController *);
    };
}
