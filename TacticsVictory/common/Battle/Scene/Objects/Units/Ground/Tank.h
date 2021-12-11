// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Units/Ground/GroundUnit.h"


namespace Pi
{
    class TankController;


    // ----------------------------------------------------------------------------------------------------------------
    class Tank : public GroundUnitObject
    {
    public:

        static GameObject *Create();

    private:

        ControllerReg<TankController> tankControllerRegistration {PiTypeGroundUnitObject::Tank, "Tank"};
        ModelRegistration             tankModelRegistration {PiTypeGroundUnitObject::Tank, "Tank", "models/Tank",
                                        ModelRegistrationFlag::Precache, PiTypeGroundUnitObject::Tank};

        Tank() : GroundUnitObject(PiTypeGroundUnitObject::Tank) {};
        virtual ~Tank() {};
    };


    // ----------------------------------------------------------------------------------------------------------------
    class TankController final : public GroundUnitController
    {

    public:

        TankController();
        ~TankController();

        void Preprocess() override;

    private:

        TankController(const TankController &tankController);

        Controller *Replicate() const override;
    };

}
