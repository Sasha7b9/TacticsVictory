#include <stdafx.h>


#include "Terrain.h"
#include "Game/Objects/Plane.h"
#include "Game//Objects/TerrainBlock.h"


vTerrain::vTerrain(Vector<Vector<float> > &map_) : Object(gContext), map(map_)
{
    uint mapSizeX = map[0].Size();
    uint mapSizeZ = map.Size();

    numBlocksInZ = mapSizeZ / sizeBlock;
    numBlocksInX = mapSizeX / sizeBlock;

    blocks.Resize(numBlocksInZ);

    for(uint i = 0; i < blocks.Size(); i++)
    {
        blocks[i].Resize(numBlocksInX);
    }

    for(uint x = 0; x < numBlocksInX; x++)
    {
        for(uint z = 0; z < numBlocksInZ; z++)
        {
            Vector<Vector<float> > subMap = ExtractSubMap(x  * sizeBlock, z * sizeBlock, sizeBlock);
            SharedPtr<vTerrainBlock> block(new vTerrainBlock(subMap, {(float)(x * sizeBlock) - 1.0f, 0.0f, -(float)(z * sizeBlock) + 1.0f}));
            blocks[z][x] = block;
        }
    }
}

void vTerrain::SetHeight(uint row, uint col, float height)
{
    map[row][col] = height;

    uint posZ = row / sizeBlock;
    uint posX = col / sizeBlock;

    Vector<Vector<float> > subMap = ExtractSubMap(posX * sizeBlock, posZ * sizeBlock, sizeBlock);
    blocks[posZ][posZ]->Rebuild(subMap);
}

// NOTE Size of the returned array size + 2
Vector<Vector<float> > vTerrain::ExtractSubMap(uint startX, uint startZ, uint size)
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

vPlane vTerrain::GetIntersection(Ray &ray)
{
    vPlane plane = vPlane::ZERO;
    Vector<float> distances;
    Vector<vPlane> planes;
    for(uint x = 0; x < numBlocksInX; x++)
    {
        for(uint z = 0; z < numBlocksInZ; z++)
        {
            bool isClosing = true;
            float distance = blocks[z][x]->GetIntersection(ray, plane, isClosing);
            if(distance != Urho3D::M_INFINITY)
            {
                distances.Push(distance);
                planes.Push(isClosing ? vPlane::ZERO : plane);
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
        plane = vPlane::ZERO;
    }

    return plane;
}