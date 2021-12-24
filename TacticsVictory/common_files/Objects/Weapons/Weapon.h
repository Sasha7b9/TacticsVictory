// 2021/12/15 19:16:25 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/GameObject_.h"


namespace Pi
{
    class WeaponController;

    class WeaponObject : public GameObject
    {
    protected:

        WeaponObject(TypeWeapon, int, WeaponController *);

    private:

        TypeWeapon typeWeapon;
    };


    class WeaponController : public GameObjectController
    {
    public:

        virtual ~WeaponController() {};

    protected:

        WeaponController(WeaponObject *);
    };
}
