// 2021/12/17 0:04:45 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    class UnitController;

    // Выбирает цели и производит стрельбу на основании поступающих заданий и окружающей обстановки
    class Shooter
    {
    public:

        virtual ~Shooter() {}

        static Shooter *New(UnitController *);

        void Update(float dT);

    protected:

        Shooter(UnitController *);

        UnitController *controller = nullptr;
    };
}
