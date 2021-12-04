// 2021/12/4 11:09:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{

    namespace WaveAlgorithm
    {
        // Установить новые параметры для расчёта и рассчитать
        void Calculate(const Point2D &start, const Point2D &end);

        // Включить отображение
        void Enable();

        // Отключить отображение
        void Disable();

        // Возвращает true, если путь найден
        bool PathIsFound();

        // Возвращает найденный путь
        Array<Point2D> GetPath();

        void Destroy();
    }

}