// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Ground/GroundUnit.h"


namespace Pi
{
    class TankController;


    // ----------------------------------------------------------------------------------------------------------------
    class Tank : public GroundUnitObject
    {
    public:

        static GameObject *Create();

    private:

        ControllerReg<TankController> tankControllerRegistration {TTypeGroundUnit::Tank, "Tank"};
        ModelRegistration             tankModelRegistration {TTypeGroundUnit::Tank, "Tank", "models/Tank",
                                        ModelRegistrationFlag::Precache, TTypeGroundUnit::Tank};

        Tank() : GroundUnitObject(TTypeGroundUnit::Tank) {};
        virtual ~Tank() {};
    };


    // ----------------------------------------------------------------------------------------------------------------
    class TankController : public GroundUnitController
    {
    public:

        TankController();
        virtual ~TankController();

        virtual void Preprocess() override;

    private:

        TankController(const TankController &);

        virtual Controller *Replicate() const override;
    };

}
