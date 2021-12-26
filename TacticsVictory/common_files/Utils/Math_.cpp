// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Utils/Math_.h"


using namespace Pi;


uint M::RandomLargeUINT(uint range) {
    return (Math::Random(65535) << 24) | (Math::Random(65535) << 16) | (Math::Random(65535) << 8) | Math::Random(65535) % range;
}

ColorRGBA M::RandomColor(bool alpha) {
    ColorRGBA color(Math::RandomFloat(1.0f), Math::RandomFloat(1.0f), Math::RandomFloat(1.0f));
    if(alpha) {
        color.alpha = Math::RandomFloat(1.0f);
    }
    return color;
}

uint M::ColorToUINT(const ColorRGBA &color) {
    uint red = (uint)(color.red * 255);
    uint green = (uint)(color.green * 255);
    uint blue = (uint)(color.blue * 255);
    uint alpha = (uint)(color.alpha * 255);

    return red | (green << 8) | (blue << 16) | (alpha << 24);
}

ColorRGBA M::SetColorBrightness(const ColorRGBA &color, float brightness) {
    float maxComponent = color.red;
    if(color.green > maxComponent) {
        maxComponent = color.green;
    }
    if(color.blue > maxComponent) {
        maxComponent = color.blue;
    }

    float koeff = 1.0f / maxComponent;

    ColorRGBA color100 = ColorRGBA(color.red * koeff, color.green * koeff, color.blue * koeff, color.alpha);

    return ColorRGBA(color100.red * brightness, color100.green * brightness, color100.blue * brightness, color.alpha);
}

bool M::PointInRect(const Point2D *point, float xRect, float yRect, float widthRect, float heightRect) {
    float rightRect = xRect + widthRect;
    float bottomRect = yRect + heightRect;
    return (point->x >= xRect && point->x <= rightRect && point->y >= yRect && point->y <= bottomRect);
}


Point2D M::InvertPoint2D(Point2D &point) {
    point.x = -point.x;
    point.y = -point.y;
    return point;
}

ColorRGBA M::OneComplement(const ColorRGBA &color) {
    return ColorRGBA(1.0f - color.red, 1.0f - color.green, 1.0f - color.blue);
}

float M::LimitationFloat(float value, float min, float max) {
    if(value < min) {
        return min;
    }
    if(value > max) {
        return max;
    }
    return value;
}

bool M::BetweenTwoPoints(const Point2D &p0, const Point2D &p1, const Point2D &value) {
    int l = (int)p0.x;
    int r = (int)p1.x;
    int t = (int)p0.y;
    int b = (int)p1.y;
    if (l > r) {
        Exchange(l, r);
    }
    if (t > b) {
        Exchange(t, b);
    }

    Rect rect(l - 1, t - 1, r + 1, b + 1);

    return rect.Contains({ (int)value.x, (int)value.y });
}