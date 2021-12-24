// 2021/12/15 21:04:33 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Air/AirUnit_.h"


namespace Pi
{
    class Airplane : public AirUnitObject
    {
    public:

        static Airplane *Create(int id = -1);

    private:

        Airplane(int id = -1);

        virtual ~Airplane();
    };


    class AirplaneController final : public AirUnitController
    {
    public:

        AirplaneController(Airplane *);
        virtual ~AirplaneController();

        virtual void Preprocess() override;
        virtual void Move(float dT) override;

    private:

        const static UnitParameters parameters;
    };


    class CommanderAirplane : public Commander
    {
        friend class Commander;

    public:

        virtual ~CommanderAirplane() {}

    protected:

        CommanderAirplane(UnitController *);
    };


    class DriverAirplane : public Driver
    {
        friend class Driver;

    public:

        virtual ~DriverAirplane() {}

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
