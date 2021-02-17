/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "Scene/Objects/Terrain/_TTerrain.h"


extern TerrainTV *TheTerrain;


struct Coord
{
    Coord(const Coord &coord) : row(coord.row), col(coord.col) { }

    Coord(uint row_ = 0U, uint col_ = 0U) : row(row_), col(col_) { }

    uint row = 0;
    uint col = 0;

    bool operator ==(const Coord& rhs) const
    {
        return row == rhs.row && col == rhs.col;
    }
    Coord& operator =(const Coord& rhs)
    {
        row = rhs.row;
        col = rhs.col;
        return *this;
    }

    Vector3 ToVector3() const
    {
        Vector3 retValue;

        retValue.x_ = static_cast<float>(col) + 0.5f;
        retValue.y_ = TheTerrain->GetHeight(row, col);
        retValue.z_ = -static_cast<float>(row) - 0.5f;

        return retValue;
    }

    static void RegisterInAS();
};
