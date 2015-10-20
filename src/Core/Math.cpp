#include <stdafx.h>


#include "Math.h"


int Math::CircularIncrease(int value, int min, int max)
{
    ++value;
    return (value > max) ? min : value;
}
