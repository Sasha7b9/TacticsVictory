// 2021/12/15 21:04:33 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Air/AirUnit_.h"


namespace Pi
{
    class SmokeTrailParticleSystem;


    class Airplane : public AirUnitObject, public MapElement<Airplane>
    {
    public:
        static Airplane *Create(int id = -1);
        static Map<Airplane> objects;
        static SmokeTrailParticleSystem *smokeTrail;
    private:
        Airplane(int id = -1);
        virtual ~Airplane() {}
        static const GameObjectParameters parameters;
    };
}
