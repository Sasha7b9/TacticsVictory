#include <stdafx.h>


#include "Terrain.h"


Vector<Vector<PODVector<CubeTerrain*>>> Terrain::columnsCubes;


Terrain::Terrain(Context *context) :
    Object(context)
{
}

Terrain::~Terrain()
{
    for(auto &row : columnsCubes)
    {
        for(auto &col : row)
        {
            for(auto &cube : col)
            {
                cube = nullptr;
            }
        }
    }
}

void Terrain::CreateFromVector(Vector<Vector<float>> &level)
{
    float time = gTime->GetElapsedTime();

    this->level = level;

    CubeTerrain::terrain = this;

    uint height = SegmentTerrain::HEIGHT;
    uint width = SegmentTerrain::WIDTH;

    uint segmentsInZ = level.Size() / height + ((level.Size() % height) == 0 ? 0 : 1);
    uint segmentsInX = level[0].Size() / width + ((level.Size() % width) == 0 ? 0 : 1);

    uint allRows = level.Size();
    uint allCols = level[0].Size();

    columnsCubes.Resize(allRows);

    for(auto &row : columnsCubes)
    {
        row.Resize(allCols);
    }

    segments.Resize(segmentsInZ);

    for(uint row0 = 0; row0 < allRows; row0 += height)
    {
        segments[row0 / height].Resize(segmentsInX);

        for(uint col0 = 0; col0 < allCols; col0 += width)
        {
            uint numRows = (row0 + height > allRows) ? (allRows - row0) : height;
            uint numCols = (col0 + width > allCols) ? (allCols - col0) : width;

            uint i = row0 / height;
            uint j = col0 / width;

            segments[i][j] = new SegmentTerrain();

            segments[i][j]->CreateFromVector(level, row0, col0, numRows, numCols);
        }
    }

    for(uint z = 0; z < segmentsInZ; z++)
    {
        for(uint x = 0; x < segmentsInX; x++)
        {
            SegmentTerrain *segment = segments[z][x];
            if(x > 0)
            {
                segment->neighbours[SegmentTerrain::LEFT] = segments[z][x - 1];
            }
            if(z > 0)
            {
                segment->neighbours[SegmentTerrain::TOP] = segments[z - 1][x];
            }
            if(x < segmentsInX - 1)
            {
                segment->neighbours[SegmentTerrain::RIGHT] = segments[z][x + 1];
            }
            if(z < segmentsInZ - 1)
            {
                segment->neighbours[SegmentTerrain::BOTTOM] = segments[z + 1][x];
            }
        }
    }

    for(auto row : segments)
    {
        for(SegmentTerrain* segment : row)
        {
            segment->Build();
        }
    }

    URHO3D_LOGINFOF("time create terrain %f sec", gTime->GetElapsedTime() - time);
}

void Terrain::SaveToFile(char * /*nameFile*/)
{

}

float Terrain::GetHeight(uint row, uint col)
{
    return level[row][col];
}

void Terrain::SetHeight(uint row, uint col, float height)
{
    level[row][col] = height;
}

void Terrain::Update()
{

}

uint Terrain::NumRows()
{
    return level.Size();
}

uint Terrain::NumCols()
{
    return level[0].Size();
}

bool Terrain::Empty()
{
    return level.Empty();
}

Plane Terrain::GetIntersectionPlane(Ray& /*ray*/)
{
    return Plane::ZERO;
}

Line Terrain::GetIntersectionEdge(Ray &/*ray*/)
{
    return Line::ZERO;
}

Plane Terrain::GetPlane(uint /*row*/, uint /*col*/)
{
    return Plane::ZERO;
}

Vector<Vector<float>> Terrain::GetMap()
{
    return level;
}

PODVector<CubeTerrain*>* Terrain::GetColumnCubes(CubeTerrain *cube, DIR dir)
{
    const int dRow[8] = { 0, -1, -1, -1, 0, 1, 1,  1};
    const int dCol[8] = {-1, -1,  0,  1, 1, 1, 0, -1};

    uint row = (uint)((int)cube->row + dRow[dir]);
    uint col = (uint)((int)cube->col + dCol[dir]);

    if(row > NumRows() - 1 || col > NumCols() - 1)
    {
        return nullptr;
    }

    return &columnsCubes[row][col];
}

SegmentTerrain* Terrain::GetSegmentForCoord(uint row, uint col)
{
    return segments[row / SegmentTerrain::HEIGHT][col / SegmentTerrain::WIDTH];
}
