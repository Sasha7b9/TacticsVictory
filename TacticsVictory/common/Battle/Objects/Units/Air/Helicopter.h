// 2021/12/15 21:15:28 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Air/AirUnit.h"


namespace Pi
{
    class Helicopter : public AirUnitObject
    {
    public:

        static GameObject *Create();

    private:

        Helicopter() : AirUnitObject(TypeAirUnit::Helicopter) {};
        virtual ~Helicopter() {};
    };


    class HelicopterController final : public AirUnitController
    {
    public:

        HelicopterController();
        ~HelicopterController();

        virtual void Preprocess() override;

    private:

        static UnitParameters parameters;

        HelicopterController(const HelicopterController &);

        virtual Controller *Replicate() const override;
    };


    class NavigatorHelicopter : public Commander
    {
        friend class Commander;

    public:

        virtual ~NavigatorHelicopter() {}

        virtual void Update(float dT) override;

    protected:

        NavigatorHelicopter(UnitController *);
    };


    class DriverHelicopter : public Driver
    {
        friend class Driver;

    public:

        virtual ~DriverHelicopter() {}

        virtual void Update(float dT) override;

    protected:

        DriverHelicopter(UnitController *);
    };


    class ShooterHelicopter : public Shooter
    {
        friend class Shooter;

    public:

        virtual ~ShooterHelicopter() {}

    protected:

        ShooterHelicopter(UnitController *);
    };
}
