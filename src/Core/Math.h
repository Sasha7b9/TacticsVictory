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
};