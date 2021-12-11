// 2021/12/11 11:21:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    class Point2DI
    {
    public:
        Point2DI(int _x = 0, int _y = 0) : x(_x), y(_y) {}
        Point2DI(const Point2D &point) : x((int)point.x), y((int)point.y) {}
        bool operator==(const Point2DI &rhs) const { return x == rhs.x && y == rhs.y; }
        bool operator!=(const Point2DI &rhs) const { return x != rhs.x || y != rhs.y; }
        int x;
        int y;
    };
}
