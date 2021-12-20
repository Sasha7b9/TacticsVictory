// 2021/12/15 19:43:21 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Ammo/Ammo_.h"


namespace Pi
{
    class Rocket : public AmmoObject
    {
    public:

        static GameObject *Create();

    private:

        Rocket() : AmmoObject(TypeAmmo::Rocket) {};
        virtual ~Rocket() {};
    };


    class RocketController : public AmmoController
    {
    public:

        RocketController();
        ~RocketController();

        virtual void Preprocess() override;

    private:

        RocketController(const RocketController &controller);

        virtual Controller *Replicate() const override;
    };
}
