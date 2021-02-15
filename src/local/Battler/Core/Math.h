/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once


#define ABS(x) ((x) < 0 ? -(x) : (x))


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

    static int RandomInt(int min, int max)
    {
        int rnd = Rand();

        int delta = max - min + 1;

        return (rnd % delta) + min;
    }

    template <class T> static T Min(T val0, T val1, T val2, T val3)
    {
        T min = val0;
        if(val1 < min)
        {
            min = val1;
        }
        if(val2 < min)
        {
            min = val2;
        }
        if(val3 < min)
        {
            min = val3;
        }
        return min;
    }

    template <class T> static T Max(T val0, T val1, T val2, T val3)
    {
        T max = val0;
        if(val1 > max)
        {
            max = val1;
        }
        if(val2 > max)
        {
            max = val2;
        }
        if(val3 > max)
        {
            max = val3;
        }
        return max;
    }

    template <class T> static T Max(T val0, T val1, T val2)
    {
        T max = val0;
        if (val1 > max)
        {
            max = val1;
        }
        if (val2 > max)
        {
            max = val2;
        }
        return max;
    }

    static BoundingBox CalculateBoundingBox(const float *buffer, uint numVertexes);   // format MASK_POSITION | MASK_NORMAL | MASK_TEXCOORD1
};
