// 2021/12/15 19:42:33 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Ammo/Ammo_.h"


namespace Pi
{
    class Bullet : public AmmoObject
    {
    public:

        static GameObject *Create();

    private:

        Bullet(int id = -1);
        virtual ~Bullet() {};
    };


    class BulletController : public AmmoController
    {
    public:

        BulletController(Bullet *);

        virtual ~BulletController();

        virtual void Preprocess() override;

    private:

        BulletController(const BulletController &);
    };
}
