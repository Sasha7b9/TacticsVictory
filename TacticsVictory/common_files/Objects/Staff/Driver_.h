// 2021/12/17 0:02:58 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Unit_.h"


namespace Pi
{
    class DriverTask;
    struct GameObjectParameters;


    // Класс для управления передвижением юнита по маршрутам, проложенным штурманом (Navigator)
    class Driver
    {
        friend class Commander;
        friend class DriverTask;
        friend class UnitController;
    public:
        Driver(GameObject *);

        virtual ~Driver();

        void AppendTask(DriverTask *);

        virtual void Update(float dT);

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

        static Driver *Create(GameObject *);

    protected:

        GameObject *const object = nullptr;

        GameObjectParameters *const params = nullptr;

    private:

        Array<DriverTask *>  tasks;

        // Собрать статистику по завершении Update()
        void ApplyTransform();

        bool EmptyTaskList() const { return tasks.GetElementCount() == 0; };
    };
}