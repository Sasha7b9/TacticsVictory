// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    namespace M
    {
        uint         RandomLargeUINT(uint range);
        ColorRGBA    RandomColor(bool alpha = false);
        uint         ColorToUINT(const ColorRGBA &color);
        ColorRGBA    UINTtoColor(uint);
        ColorRGBA    SetColorBrightness(const ColorRGBA &color, float bightness);       // brightness = 0.0f ... 1.0F;
        bool         PointInRect(const Point2D *point, float xRect, float yRect, float widthRect, float heightRect);
        Point2D      InvertPoint2D(Point2D &point);
        ColorRGBA    OneComplement(const ColorRGBA &color);
        float        LimitationFloat(float value, float min, float max);
        bool         BetweenTwoPoints(const Point2D &p0, const Point2D &p1, const Point2D &value);

        template<class T>
        void Swap(T &value1, T &value2)
        {
            T temp = value1;
            value1 = value2;
            value2 = temp;
        }

        // ??????????? ?? ???????????
        template<class T>
        void PutInOrder(T &value1, T &value2)
        {
            if (value2 < value1)
            {
                Swap<T>(value1, value2);
            }
        }

        template<class T>
        T LimitationAbove(T value, T max)
        {
            return (value > max) ? max : value;
        }
    }
}
