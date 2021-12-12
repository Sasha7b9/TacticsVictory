// 2021/12/12 21:37:13 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Utils/Point2DI.h"


namespace Pi
{
    // Класс для визуализации пути юнита
    class PathMapping
    {
    public:
        void CreateFrom(const Array<Point2DI> &path);
    private:
        Array<Point2D> path;
    };
}
