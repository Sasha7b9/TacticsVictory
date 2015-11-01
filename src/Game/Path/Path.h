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
        bool isCalculated = false;      // If true, path for end point is calculated;
    };

    Vector<Vector<StructPath>> paths;   // Here stored calculated paths to end;

    void Prepare();
    void CalculatePath(Coord start, Coord end);
};
