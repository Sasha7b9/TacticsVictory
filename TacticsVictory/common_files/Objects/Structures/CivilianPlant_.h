// 2021/12/15 19:37:21 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Structures/Structure_.h"


namespace Pi
{
    class CivilianPlant : public StructureObject
    {
    public:

        static GameObject *Create();

    private:

        CivilianPlant() : StructureObject(TypeStructure::CivilianPlant) {};
        virtual ~CivilianPlant() {};
    };


    class CivilianPlantController : public StructureController
    {
    public:

        CivilianPlantController();
        virtual ~CivilianPlantController();

        virtual void Preprocess() override;

    private:

        CivilianPlantController(const CivilianPlantController &controller);

        virtual Controller *Replicate() const override;
    };
}
