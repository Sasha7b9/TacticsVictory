// 2021/12/15 21:04:33 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Air/AirUnit.h"


namespace Pi
{
    class Airplane : public AirUnitObject
    {
    public:

        static Airplane *Create();

    private:

        Airplane();

        virtual ~Airplane();
    };


    class AirplaneController final : public AirUnitController
    {
    public:

        AirplaneController();
        ~AirplaneController();

        virtual void Preprocess() override;
        virtual void Move() override;

    private:

        static UnitParameters parameters;

        AirplaneController(const AirplaneController &);

        virtual Controller *Replicate() const override;
    };


    class NavigatorAirplane : public Commander
    {
        friend class Commander;

    public:

        virtual ~NavigatorAirplane() {}

        virtual void Update(float dT) override;

    protected:

        NavigatorAirplane(UnitController *);
    };


    class DriverAirplane : public Driver
    {
        friend class Driver;

    public:

        virtual ~DriverAirplane() {}

        virtual void Update(float dT) override;

    protected:

        DriverAirplane(UnitController *);
    };


    class ShooterAirplane : public Shooter
    {
        friend class Shooter;

    public:

        virtual ~ShooterAirplane() {}

    protected:

        ShooterAirplane(UnitController *);
    };
}
