// 2021/12/15 22:30:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Weapons/Weapon.h"


namespace Pi
{
    class RocketLauncher : public WeaponObject
    {
    public:

        static GameObject *Create();

    private:

        RocketLauncher() : WeaponObject(TTypeWeapon::RocketLauncher) {};
        virtual ~RocketLauncher() {};
    };


    class RocketLauncherController : public WeaponController
    {
    public:

        RocketLauncherController();
        virtual ~RocketLauncherController();

        virtual void Preprocess() override;

    private:

        RocketLauncherController(const RocketLauncherController &);

        virtual Controller *Replicate() const override;
    };
}
