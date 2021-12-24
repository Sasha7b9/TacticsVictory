// 2021/12/17 0:02:58 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Unit_.h"


namespace Pi
{
    class DriverTask
    {
    public:

        DriverTask(Driver *driver);

        virtual ~DriverTask() {}

        // Выполняется каждый кадр
        virtual void RunStep(float dT) = 0;

        // Возвращает true, если задавние завершено
        bool Completed() const { return completed; }

    protected:

        UnitObject *unit = nullptr;
        UnitController * const controller = nullptr;
        bool completed = false;

        // Эта функция вызывается, когда задание завершено
        virtual void ExecuteAfterCompletion() = 0;
    };


    class DriverTaskDive : public DriverTask
    {
    public:

        DriverTaskDive(Driver *driver, float z);

        virtual ~DriverTaskDive() {}

        virtual void RunStep(float dT) override;

    private:

        float destination_z = 0.0f;
        float position_z = 0.0f;
        float speed = 0.0f;

        virtual void ExecuteAfterCompletion() override;
    };


    class DriverTaskMove : public DriverTask
    {
    public:

        DriverTaskMove(Driver *driver, const Point3D &pointTo);

        virtual ~DriverTaskMove() {}

        virtual void RunStep(float dT) override;

    private:

        virtual void ExecuteAfterCompletion() override;

        Point3D destination = Point3D::ZERO;
        Vector3D speed = Vector3D::ZERO;
        Point3D position = Point3D::ZERO;
    };


    class DriverTaskRotate : public DriverTask
    {
    public:

        DriverTaskRotate(Driver *driver, const Vector3D &axis, float angle);

        virtual void RunStep(float dT) override;

    private:

        Vector3D axis;
        const float target_angle;   // На такой угол нужно повернуться
        float rotated = 0.0f;       // На такой угол мы уже повернулись

        virtual void ExecuteAfterCompletion() override;
    };


    // Класс для управления передвижением юнита по маршрутам, проложенным штурманом (Navigator)
    class Driver
    {
    public:

        virtual ~Driver();

        UnitController *const controller = nullptr;

        static Driver *New(UnitController *);

        void Update(float dT);

        void AppendTask(DriverTask *);

        bool EmptyTaskList() const { return tasks.GetElementCount() == 0; };

    protected:

        Driver(UnitController *controller);

        UnitObject *unit = nullptr;

        Array<DriverTask *> tasks;
    };
}