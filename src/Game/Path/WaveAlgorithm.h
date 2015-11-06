#pragma once


#include "Game/Objects/Terrain.h"


#pragma warning(push)
#pragma warning(disable:4520)
struct Coord
{
    Coord(uint row_ = 0U, uint col_ = 0U) : row(row_), col(col_)
    {
    }

    uint row = 0;
    uint col = 0;
    Vector3 vect;

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

    Vector3& ToVector3()
    {
        vect.x_ = (float)col + 0.5f;
        vect.y_ = gTerrain->GetHeight(row, col);
        vect.z_ = -(float)row - 0.5f;

        return vect;
    }
};
#pragma warning(pop)


class WaveAlgorithm : public Thread
{
public:
    
    WaveAlgorithm();
    ~WaveAlgorithm();
    void SetSize(uint numRows, uint numCols);

    void StartFind(Coord start, Coord end);
    bool PathIsFound();
    PODVector<Coord> GetPath();

    virtual void ThreadFunction();

private:
  
    typedef Vector<Coord> Wave;

    struct Cell
    {
        Cell() : numWave(-1) {};
        int numWave = -1;
    };

    enum Dir
    {
        LEFT
    };

    struct KeySet
    {
        KeySet(int i_ = 0, Dir dir_ = LEFT) : i(i_), dir(dir_) {};
        int i;
        Dir dir;
    };

    HashSet<KeySet> passValues;

    Vector<Vector<Cell>> cells;
    float heightStart = 0.0f;

    uint numRows = 0;
    uint numCols = 0;

    PODVector<Coord> path;
    Coord start;
    Coord end;

    bool pathIsFound = true;

    bool Contain(Wave &wave, Coord &coord);
    void NextWave(Vector<Wave> &waves);
    void SetCell(Wave &wave, uint row, uint col, int numWave);
    void AddPrevWave(PODVector<Coord> &path);
    void FindPath();
};
