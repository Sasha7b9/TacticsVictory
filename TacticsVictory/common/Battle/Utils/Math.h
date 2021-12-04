// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{

    class Mathem {
    public:
        static uint         RandomLargeUINT(uint range);
        static ColorRGBA    RandomColor(bool alpha = false);
        static uint         ColorToUINT(const ColorRGBA &color);
        static ColorRGBA    SetColorBrightness(const ColorRGBA &color, float bightness);       // brightness = 0.0f ... 1.0F;
        static bool         PointInRect(const Point2D *point, float xRect, float yRect, float widthRect, float heightRect);
        static Point2D      InvertPoint2D(Point2D &point);
        static ColorRGBA    OneComplement(const ColorRGBA &color);
        //static Vector2D     Integer2D2Vector2D(const Integer2D &value) { return Vector2D((float)value.x, (float)value.y); };
        static float        LimitationFloat(float value, float min, float max);
        static bool         BetweenTwoPoints(const Point2D &p0, const Point2D &p1, const Point2D &value);
    };

}
