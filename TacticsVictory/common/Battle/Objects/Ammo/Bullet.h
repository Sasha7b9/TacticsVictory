// 2021/12/15 19:42:33 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Ammo/Ammo.h"


namespace Pi
{
    class Bullet : public AmmoObject
    {
    public:

        static GameObject *Create();

    private:

        Bullet() : AmmoObject(TTypeAmmo::Bullet) {};
        virtual ~Bullet() {};
    };


    class BulletController : public AmmoController
    {
    public:

        BulletController();
        virtual ~BulletController();

        virtual void Preprocess() override;

    private:

        BulletController(const BulletController &);

        virtual Controller *Replicate() const override;
    };
}
