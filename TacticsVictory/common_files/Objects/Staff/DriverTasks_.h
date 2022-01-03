// 2021/12/28 12:17:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    class Driver;
    class GameObject;
    struct GameObjectParameters;


    class DriverTask
    {
    public:

        enum class Type
        {
            Stop,
            Dive,
            Move,
            Rotate,
            FreeFlight
        };

        DriverTask(Driver *driver);
        virtual ~DriverTask() { }

        virtual void Preprocess() { }

        // Выполняется каждый кадр
        virtual void RunStep(float dT);

        // Возвращает true, если задавние завершено
        bool Completed() const { return completed; }

    protected:

        GameObject           &object;
        Driver               &driver;
        GameObjectParameters &params;
        bool                  completed = false;
        bool                  first     = true;
    };


    // Выровнять направление к ближайшему возможному (из восьми возможных)
    class DriverTaskAlignDirection : public DriverTask
    {
    public:
        DriverTaskAlignDirection(Driver *driver);
        virtual void RunStep(float dT) override;
    };


    class DriverTaskMove : public DriverTask
    {
    public:

        struct Direction
        {
            typedef uint B;

            static const B Forward = 1 << 0;
            static const B Left    = 1 << 1;
            static const B Right   = 1 << 2;
            static const B Back    = 1 << 3;
        };

        DriverTaskMove(Driver *driver, Direction::B direction);
        virtual ~DriverTaskMove() { }
        virtual void RunStep(float dT) override;
    private:
        Direction::B direction = 0;
        virtual void Preprocess() override;
    };


    // Повернуть по часовой стрелке к ближайшему возможному направлению
    class DriverTaskTurnClockwise : public DriverTask
    {
    public:
        DriverTaskTurnClockwise(Driver *driver);
        virtual ~DriverTaskTurnClockwise() { }
        virtual void RunStep(float dT) override;
    private:
        
    };


    class DriverTaskRotate : public DriverTask
    {
    public:
        DriverTaskRotate(Driver *driver, const Vector3D &axis, float angle);
        virtual void RunStep(float dT) override;
    private:
        Vector3D    axis;
        const float target_angle;           // На такой угол нужно повернуться
        float       rotated = 0.0f;         // На такой угол мы уже повернулись
        Vector3D    target_direction;
        Vector3D    target_up;
    };


    class DriverTaskDive : public DriverTask
    {
    public:
        DriverTaskDive(Driver *driver, float z);
        virtual ~DriverTaskDive() { }
        virtual void RunStep(float dT) override;
    private:
        float destination_z = 0.0f;
        float position_z    = 0.0f;
        float speed         = 0.0f;
    };


    // Режим "свободного полёта"
    class DriverAirplaneTaskFreeFlight : public DriverTask
    {
    public:
        DriverAirplaneTaskFreeFlight(Driver *);
        virtual void RunStep(float dT) override;
    };
}
