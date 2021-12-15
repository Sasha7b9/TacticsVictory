// 2021/12/15 21:04:33 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Air/AirUnit.h"


namespace Pi
{
    class Airplane : public AirUnitObject
    {
    public:

        static Airplane *Create();

    private:

        Airplane();

        virtual ~Airplane();
    };


    class AirplaneController final : public AirUnitController
    {
    public:

        AirplaneController();
        ~AirplaneController();

        virtual void Preprocess() override;
        virtual void Move() override;

    private:

        AirplaneController(const AirplaneController &);

        virtual Controller *Replicate() const override;
    };
}
