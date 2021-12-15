// 2021/12/15 22:18:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Weapons/Weapon.h"


namespace Pi
{
    class Laser : public WeaponObject
    {
    public:

        static GameObject *Create();

    private:

        Laser() : WeaponObject(TTypeWeapon::Laser) {};
        virtual ~Laser() {};
    };


    class LaserController : public WeaponController
    {
    public:

        LaserController();
        virtual ~LaserController();

        virtual void Preprocess() override;

    private:

        LaserController(const LaserController &);

        virtual Controller *Replicate() const override;
    };
}

