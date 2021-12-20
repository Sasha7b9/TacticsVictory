// 2021/12/15 19:16:25 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/GameObject_.h"


namespace Pi
{
    class WeaponObject : public GameObject
    {
    protected:

        WeaponObject(TypeWeapon::S type) : GameObject(TypeGameObject::Weapon), typeWeapon(type) {};

    private:

        TypeWeapon::S typeWeapon;
    };


    class WeaponController : public GameObjectController
    {
    public:

        virtual ~WeaponController() {};

    protected:

        WeaponController(PiTypeController::S type);
    };
}
