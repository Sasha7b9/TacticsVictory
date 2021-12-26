// 2021/12/15 21:04:33 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Air/AirUnit_.h"


namespace Pi
{
    class Airplane : public AirUnitObject, public MapElement<Airplane>
    {
    public:
        static Airplane *Create(int id = -1);
        static Map<Airplane> objects;
    private:
        Airplane(int id = -1);
        virtual ~Airplane() {}
    };


    class AirplaneController final : public AirUnitController
    {
        friend class Airplane;
    private:
        AirplaneController(Airplane *airplane) : AirUnitController(airplane, parameters) { }
        virtual ~AirplaneController() {};
        const static UnitParameters parameters;
    };


    class DriverAirplane : public Driver
    {
        friend class Driver;
    private:
        DriverAirplane(UnitController *controller) : Driver(controller) { }
        virtual ~DriverAirplane() {}
        virtual void Update(float dT) override;
    };
}
