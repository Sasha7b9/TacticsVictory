// 2021/12/15 19:16:25 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/GameObject.h"


namespace Pi
{
    class WeaponObject : public GameObject
    {
    protected:

        WeaponObject(TTypeWeapon::S type) : GameObject(TTypeGameObject::Weapon), typeWeapon(type) {};

    private:

        TTypeWeapon::S typeWeapon;
    };


    class WeaponController : public GameObjectController
    {
    public:

        virtual ~WeaponController() {};

    protected:

        WeaponController(PiTypeController::S type);
    };
}
