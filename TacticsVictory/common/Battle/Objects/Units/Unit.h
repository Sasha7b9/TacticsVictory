// 2021/12/1 9:47:27 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/GameObject.h"


namespace Pi
{
    // ----------------------------------------------------------------------------------------------------------------
    class UnitObject : public GameObject
    {
    public:

        static void Construct();
        static void Destruct();

    protected:

        UnitObject(TTypeUnit::S type);

    private:

        TTypeUnit::S typeUnit;
    };


    // ----------------------------------------------------------------------------------------------------------------
    class UnitController : public GameObjectController
    {
    public:

        virtual ~UnitController() {};

    protected:

        UnitController(PiTypeController::S type);
    };
}
