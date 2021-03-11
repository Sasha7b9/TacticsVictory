// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Terrain/Terrain_.h"


extern TerrainT *TheTerrain;


struct Coord
{
    Coord(const Coord &coord) : rowX(coord.rowX), colZ(coord.colZ) { }

    Coord(uint _rowX = 0U, uint _colZ = 0U) : rowX(_rowX), colZ(_colZ) { }

    uint rowX = 0U;
    uint colZ = 0U;

    bool operator ==(const Coord& rhs) const
    {
        return (rowX == rhs.rowX) && (colZ == rhs.colZ);
    }
    Coord& operator =(const Coord& rhs)
    {
        rowX = rhs.rowX;
        colZ = rhs.colZ;
        return *this;
    }

    Vector3 ToVector3() const
    {
        Vector3 retValue;

        retValue.x_ = static_cast<float>(rowX) + 0.5f;
        retValue.y_ = TheTerrain->GetHeight(rowX, colZ);
        retValue.z_ = -static_cast<float>(colZ) + 0.5f;

        return retValue;
    }

    static void RegisterInAS();
};
