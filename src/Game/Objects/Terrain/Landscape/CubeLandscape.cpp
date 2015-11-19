#include <stdafx.h>


#include "CubeLandscape.h"


CubeLandscape::CubeLandscape()
{
    for(auto &side : sides)
    {
        side = nullptr;
    }
    for(auto &corner : corners)
    {
        corner = nullptr;
    }
    for(auto &edge : edges)
    {
        edge = nullptr;
    }
}
