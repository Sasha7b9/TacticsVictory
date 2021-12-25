// 2021/12/1 9:47:27 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/GameObject_.h"
#include "Objects/Units/Staff/Commander_.h"
#include "Objects/Units/Staff/Driver_.h"
#include "Objects/Units/Staff/Shooter_.h"
#include "Objects/Units/UnitParameters_.h"


namespace Pi
{
    class AirUnitObject;
    class GroundUnitObject;
    class WaterUnitObject;


    class UnitObject : public GameObject, public MapElement<UnitObject>
    {
    friend class UnitController;

    public:

        static void Construct();
        static void Destruct();

        const TypeUnit typeUnit;

        static Map<UnitObject> objects;

        AirUnitObject *GetAirUnit() { return typeUnit == TypeUnit::Air ? (AirUnitObject *)this : nullptr; }
        GroundUnitObject *GetGroundUnit() { return typeUnit == TypeUnit::Ground ? (GroundUnitObject *)this : nullptr; }
        WaterUnitObject *GetWaterUnit() { return typeUnit == TypeUnit::Water ? (WaterUnitObject *)this : nullptr; }
        UnitController *GetUnitController() { return (UnitController *)controller; }

    protected:

        UnitObject(TypeUnit, int, UnitController *);
    };


    class UnitController : public GameObjectController
    {
        friend class Commander;

    public:

        virtual ~UnitController();

        // Добавить задание в конец очереди (оно выполнится после всех заданий)
        UnitController *AppendTask(const CommanderTask *task);

        // Относится к воздушным юнитам
        bool BelongAir() const { return object->typeUnit == TypeUnit::Air; }

        // Относится к земельным юнитам
        bool BelongGround() const { return object->typeUnit == TypeUnit::Ground; };

        // Относится к водным юнитам
        bool BelongWater() const { return object->typeUnit == TypeUnit::Water; };

        // Возвращает указатель на AirUnitObject, если контроллер управляет таким объектом
        AirUnitObject *GetAirUnitObject() const { return BelongAir() ? (AirUnitObject *)object : nullptr; };

        // Возвращает указатель на GroundUnitObject, если контроллер управляет таким объектом
        GroundUnitObject *GetGroundUnitObject() const { return BelongGround() ? (GroundUnitObject *)object : nullptr; };

        // Возвращает указатель на WaterUnitObject, если контроллер управляет таким объектом
        WaterUnitObject *GetWaterUnitObject() const { return BelongWater() ? (WaterUnitObject *)object : nullptr; };

        // Может ли обрабатывать задания типа type
        bool CanExecute(CommanderTask::Type type) const;

        UnitParameters param;

        UnitObject * const object = nullptr;

    protected:

        UnitController(UnitObject *, const UnitParameters &);

        virtual void Preprocess() override;
        virtual void Move(float dT) override;

        Commander *commander = nullptr;     // Это командир
        Driver *driver = nullptr;           // Это водитель
        Shooter *shooter = nullptr;         // Это стрелок
    };
}
