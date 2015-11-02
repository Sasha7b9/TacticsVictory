#pragma once


#pragma warning(push)
#pragma warning(disable:4520)
struct Coord
{
    explicit Coord(int row_ = 0, int col_ = 0) : Coord((uint)row_, (uint)col_)
    {
    };
    explicit Coord(uint row_ = 0U, uint col_ = 0U) : row(row_), col(col_)
    {
    }
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
};
#pragma warning(pop)


class PathWave
{
public:

    PODVector<Coord> FindPath(Coord start, Coord end);

private:
    struct Cell
    {
        Cell() : numWave(-1) {};
        int numWave = -1;
    };

    Vector<Vector<Cell>> cells;
    float heightStart = 0.0f;

    void DrawWave(int numWave);
    void FillNearCells(uint row, uint col, int numWave);
    void AddPrevWave(PODVector<Coord> &path);
    bool StayNear(Coord coord0, Coord coord1);
};
