#pragma once
#include "Game/Objects/Terrain/Terrain.h"
#include "Core/Structures.h"


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

    Vector<Vector<int>> cells;
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
