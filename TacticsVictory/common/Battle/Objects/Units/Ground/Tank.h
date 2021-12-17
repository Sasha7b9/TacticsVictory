// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Ground/GroundUnit.h"


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

        Tank() : GroundUnitObject(TypeGroundUnit::Tank) {};
        virtual ~Tank() {};
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

        virtual Controller *Replicate() const override;
    };


    class NavigatorTank : public Commander
    {
        friend class Commander;

    public:

        virtual ~NavigatorTank() {}

        virtual void Update(float dT) override;

    protected:

        NavigatorTank(UnitController *);
    };


    class DriverTank : public Driver
    {
        friend class Driver;

    public:

        virtual ~DriverTank() {}

        virtual void Update(float dT) override;

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
