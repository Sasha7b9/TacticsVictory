#pragma once


#include "PathSegment.h"


class lPath
{
public:
    lPath();

    void SetTerrain(lTerrain *terrain);
    PODVector<Coord> GetPath(Coord start, Coord end);

private:
    lTerrain *terrain;

    struct StructPath
    {
        PODVector<Coord> path;
        PODVector<Coord> pathLeft;
        PODVector<Coord> pathRight;
        PODVector<Coord> pathTop;
        PODVector<Coord> pathBottom;
        bool isCalculated = false;
    };

    Vector<Vector<StructPath>> paths;   // Here stored calculated paths to end;

    void Prepare();
    void CalculatePath(Coord start, Coord end);
    void WritePath(PODVector<Coord> path);
    PODVector<Coord> ReversePath(PODVector<Coord> path);
};
