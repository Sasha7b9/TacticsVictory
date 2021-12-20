// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Ground/GroundUnit_.h"


namespace Pi
{
    class TankController;


    class Tank : public GroundUnitObject
    {
    public:

        static GameObject *Create();

    private:

        ControllerReg<TankController> tankControllerRegistration {TypeGroundUnit::Tank, "Tank"};
        ModelRegistration             tankModelRegistration {TypeGroundUnit::Tank, "Tank", "models/Tank",
                                      ModelRegistrationFlag::Precache, TypeGroundUnit::Tank};

        Tank();
        virtual ~Tank() {};

        Node *CreateBody();
        Node *CreateTrack(bool left);
        Node *CreateTower();
        Node *CreateBarrel();
    };


    class TankController : public GroundUnitController
    {
    public:

        TankController();

        virtual ~TankController();

        virtual void Preprocess() override;

    private:

        static UnitParameters parameters;

        TankController(const TankController &);

        TankController &operator=(const TankController &) { return *this; }

        virtual Controller *Replicate() const override;
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
