// 2021/12/17 0:02:58 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Unit_.h"


namespace Pi
{
    class DriverTask;
    struct UnitParameters;


    // Класс для управления передвижением юнита по маршрутам, проложенным штурманом (Navigator)
    class Driver
    {
        friend class Commander;
        friend class DriverTask;
        friend class UnitController;
    public:
        Driver(UnitController *);

        void AppendTask(DriverTask *);

        // Двинуть юнита вперёд
        void MoveForward(float dT);

        // Накренить
        void RotateRoll(float dT);

        // Рыскание
        void RotateYaw(float dT);

        // "Скомпенсированное" рыскание. После него азимут не сбивается
        void RotateYawCompensate(float dT);

        // Тангаж
        void RotatePitch(float dT);

        // "Скомпенсированный" тангаж. После него азимут не сбивается
        void RotatePitchCompensate(float dT);

    protected:

        virtual ~Driver();

        UnitController *const controller = nullptr;

        UnitObject *const unit = nullptr;

        UnitParameters *const param = nullptr;

    private:

        Array<DriverTask *>  tasks;

        static Driver *Create(UnitController *);

        virtual void Update(float dT);

        // Собрать статистику по завершении Update()
        void ApplyTransform();

        bool EmptyTaskList() const { return tasks.GetElementCount() == 0; };
    };
}