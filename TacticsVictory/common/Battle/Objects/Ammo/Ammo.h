// 2021/12/15 19:41:44 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/GameObject.h"


namespace Pi
{
    class AmmoObject : public GameObject
    {
    public:

        static void Construct();
        static void Destruct();

    protected:

        AmmoObject(TypeAmmo::S type) : GameObject(TypeGameObject::Ammo), typeAmmo(type) {};

    private:

        TypeAmmo::S typeAmmo;
    };


    class AmmoController : public GameObjectController
    {
    public:

        virtual ~AmmoController() {};

    protected:

        AmmoController(PiTypeController::S type);
    };
}
