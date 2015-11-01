#pragma once


struct Coord
{
    Coord(int row_ = 0, int col_ = 0) : row(row_), col(col_)
    {};
    int row = 0;
    int col = 0;
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
};


class PathSegment
{
public:

    uint row = 0;
    uint col = 0;

    struct StructSegment
    {
        PODVector<Coord> path;
        bool isCalculated = false;
    };

    Vector<Vector<PODVector<StructSegment>>> segments;     // 
};
