#include <stdafx.h>


#include "Terrain.h"


Terrain::Terrain(Context *context) :
    Object(context)
{

}

void Terrain::CreateFromVector(Vector<Vector<float>> &level)
{
    URHO3D_LOGINFOF("1 %f", gTime->GetElapsedTime());

    this->level = level;

    uint height = SegmentTerrain::HEIGHT;
    uint width = SegmentTerrain::WIDTH;

    uint segmentsInZ = level.Size() / height + ((level.Size() % height) == 0 ? 0 : 1);
    uint segmentsInX = level[0].Size() / width + ((level.Size() % width) == 0 ? 0 : 1);

    uint allRows = level.Size();
    uint allCols = level[0].Size();

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

    URHO3D_LOGINFOF("2 %f", gTime->GetElapsedTime());

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

    URHO3D_LOGINFOF("3 %f", gTime->GetElapsedTime());
    for(auto row : segments)
    {
        for(SegmentTerrain* segment : row)
        {
            segment->Build();
        }
    }
    URHO3D_LOGINFOF("4 %f", gTime->GetElapsedTime());
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
