// 2021/12/15 19:41:44 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/GameObject_.h"


namespace Pi
{
    class AmmoController;


    class AmmoObject : public GameObject
    {
    public:

        static void Construct();
        static void Destruct();

    protected:

        AmmoObject(TypeAmmo, int, AmmoController *);

        TypeAmmo typeAmmo;
    };


    class AmmoController : public GameObjectController
    {
        friend class AmmoObject;

    public:

        virtual ~AmmoController() {};

    protected:

        AmmoController(AmmoObject *);
    };
}
