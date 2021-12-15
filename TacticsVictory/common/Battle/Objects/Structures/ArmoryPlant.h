// 2021/12/15 19:36:32 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Structures/Structure.h"


namespace Pi
{
    class ArmoryPlant : public StructureObject
    {
    public:

        static GameObject *Create();

    private:

        ArmoryPlant() : StructureObject(TTypeStructure::ArmoryPlant) {};
        virtual ~ArmoryPlant() {};
    };


    class ArmoryPlantController : public StructureController
    {
    public:

        ArmoryPlantController();
        virtual ~ArmoryPlantController();

        virtual void Preprocess() override;

    private:

        ArmoryPlantController(const ArmoryPlantController &controller);

        virtual Controller *Replicate() const override;
    };
}
