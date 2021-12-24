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

        CivilianPlant(int id = -1);

        virtual ~CivilianPlant() {};
    };


    class CivilianPlantController : public StructureController
    {
        friend class CivilianPlant;

    private:

        CivilianPlantController(CivilianPlant *);

        virtual ~CivilianPlantController();

        virtual void Preprocess() override;
    };
}
