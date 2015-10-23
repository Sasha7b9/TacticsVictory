#pragma once


class Math
{
public:
    static int CircularIncrease(int value, int min, int max);
    template <class T> static int Sign(T val)
    {
        if(val == T(0)) return 0; return val < 0 ? -1 : 1;
    }

    template <class T> static bool PointsAreLocatedOneAfterAnother(T one, T two, T three)
    {
        if(one > two && two > three)
        {
            return true;
        }
        if(one < two && two < three)
        {
            return true;
        }
        return false;
    }

    template <class T> static T Limitation(T value, T min, T max)
    {
        if (value < min)
        {
            return min;
        }
        if (value > max)
        {
            return max;
        }
        return value;
    }

    template <class T> static T LimitBelow(T value, T min)
    {
        return value < min ? min : value;
    }

    template <class T> static T LimitAbove(T value, T max)
    {
        return value > max ? max : value;
    }

    static int Random(int min, int max)
    {
        int rnd = Urho3D::Rand();

        int delta = max - min + 1;

        return (rnd % delta) + min;
    }
};