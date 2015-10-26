#include <stdafx.h>


#include "Terrain.h"
#include "Game/Objects/Plane.h"
#include "Game/Objects/Line.h"
#include "Game/Objects/TerrainSegment.h"


lTerrain::lTerrain(Vector<Vector<float> > &map_) : Object(gContext), map(map_)
{
    uint mapSizeX = map[0].Size();
    uint mapSizeZ = map.Size();

    numSegmentsInZ = mapSizeZ / SIZE_SEGMENT;
    numSegmentsInX = mapSizeX / SIZE_SEGMENT;

    segments.Resize(numSegmentsInZ);
    heightChanged.Resize(numSegmentsInZ);

    for(uint i = 0; i < segments.Size(); i++)
    {
        segments[i].Resize(numSegmentsInX);
        heightChanged[i].Resize(numSegmentsInX);

        for (uint col = 0; col < numSegmentsInX; col++)
        {
            heightChanged[i][col] = false;
        }
    }

    for(uint x = 0; x < numSegmentsInX; x++)
    {
        for(uint z = 0; z < numSegmentsInZ; z++)
        {
            Vector<Vector<float>> subMap = ExtractSubMap(x  * SIZE_SEGMENT, z * SIZE_SEGMENT, SIZE_SEGMENT);
            SharedPtr<lTerrainSegment> segment(new lTerrainSegment(subMap, CalculateShift(x, z)));
            segments[z][x] = segment;
        }
    }
}

Vector3 lTerrain::CalculateShift(uint xSegment, uint zSegment)
{
    return Vector3((float)(xSegment * SIZE_SEGMENT) - 1.0f, 0.0f, -(float)(zSegment * SIZE_SEGMENT) + 1.0f);
}

lTerrain::~lTerrain()
{
    Clear();
}

uint lTerrain::NumRows()
{
    return map.Size();
}

uint lTerrain::NumCols()
{
    return map[0].Size();
}

void lTerrain::SetHeight(uint row, uint col, float height)
{
    map[row][col] = height;

    heightChanged[row / SIZE_SEGMENT][col / SIZE_SEGMENT] = true;
}

float lTerrain::GetHeight(uint row, uint col)
{
    return map[row][col];
}

lPlane lTerrain::GetPlane(uint row, uint col)
{
    uint rowSegment = row / SIZE_SEGMENT;
    uint colSegment = col / SIZE_SEGMENT;
    uint rowPlane = row - (row / SIZE_SEGMENT) * SIZE_SEGMENT;
    uint colPlane = col - (col / SIZE_SEGMENT) * SIZE_SEGMENT;
    lPlane plane = segments[rowSegment][colSegment]->GetPlane(rowPlane, colPlane);
    plane.row = row;
    plane.col = col;
    return plane;
}

void lTerrain::Update()
{
    for (uint x = 0; x < numSegmentsInX; x++)
    {
        for (uint y = 0; y < numSegmentsInZ; y++)
        {
            if (heightChanged[y][x])
            {
                uint startX = x * SIZE_SEGMENT;
                uint startY = y * SIZE_SEGMENT;
                Vector<Vector<float>> subMap = ExtractSubMap(startX, startY, SIZE_SEGMENT);
                segments[y][x]->Rebuild(subMap);
                heightChanged[y][x] = false;
            }
        }
    }
}

// NOTE Size of the returned array size + 2
Vector<Vector<float> > lTerrain::ExtractSubMap(uint startX, uint startZ, uint size)
{
    Vector<Vector<float> > subMap;
    subMap.Resize((uint)size + 2);
    
    for(uint row = 0; row < size + 2; row++)
    {
        subMap[row].Resize(size + 2);
    }

    for(uint col = 0; col < size + 2; col++)
    {
        float value = 0.0f;

        uint colMap = startX + col;

        if(startZ != 0 && colMap != 0 && colMap <= map[0].Size())
        {
            value = map[startZ - 1][colMap - 1];
        }

        subMap[0][col] = value;

        value = 0.0f;

        if(startZ + size< map.Size() && colMap < map[0].Size() && colMap != 0)
        {
            value = map[startZ + size][startX + col - 1];
        }

        subMap[size + 1][col] = value;
    }

    for(uint row = 1; row < size + 2; row++)
    {
        float value = 0.0f;

        uint absRow = startZ + row;

        if(startX != 0 && row != 0 && absRow < map.Size())
        {
            value = map[absRow - 1][startX - 1];
        }

        subMap[row][0] = value;

        value = 0.0f;

        if((startX + size != map[0].Size()) && absRow < map.Size() && absRow != 0)
        {
            value = map[startZ + row - 1][startX + size];
        }

        subMap[row][size + 1] = value;
    }

    for(uint z = startZ; z < startZ + size; z++)
    {
        for(uint x = startX; x < startX + size; x++)
        {
            subMap[z - startZ + 1][x - startX + 1] = map[z][x];
        }
    }

    return subMap;
}

lPlane lTerrain::GetIntersectionPlane(Ray &ray)
{
    lPlane plane = lPlane::ZERO;
    Vector<float> distances;
    Vector<lPlane> planes;
    for(uint x = 0; x < numSegmentsInX; x++)
    {
        for(uint z = 0; z < numSegmentsInZ; z++)
        {
            bool isClosing = true;
            float distance = segments[z][x]->GetIntersectionPlane(ray, plane, isClosing);
            if(distance != Urho3D::M_INFINITY)
            {
                distances.Push(distance);
                planes.Push(isClosing ? lPlane::ZERO : plane);
            }
        }
    }

    if(distances.Size() > 0)
    {
        float distance = distances[0];
        plane = planes[0];
        for(uint i = 1; i < distances.Size(); i++)
        {
            if(distances[i] < distance)
            {
                plane = planes[i];
            }
        }
    }
    else
    {
        plane = lPlane::ZERO;
    }

    return plane;
}

lLine lTerrain::GetIntersectionEdge(Ray &ray)
{
    lPlane plane = GetIntersectionPlane(ray);

    if (plane.IsZero())
    {
        return lLine::ZERO;
    }

    return plane.NearEdge(ray);
}

void lTerrain::Clear()
{
    map.Resize(0);

    for (auto row : segments)
    {
        for (auto block : row)
        {
            block->Clear();
        }
    }

    segments.Resize(0);
}


bool lTerrain::Empty()
{
    return segments.Empty();
}
