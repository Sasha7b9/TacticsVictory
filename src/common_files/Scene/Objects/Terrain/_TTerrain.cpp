/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include "stdafx.h"


Vector<Vector<PODVector<CubeTerrain*>>> TerrainTV::columnsCubes;


TerrainTV::TerrainTV(Context *context) : Object(context)
{
}


TerrainTV::~TerrainTV()
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


void TerrainTV::CreateFromVector(const Vector<Vector<float>> &lev)
{
    float time = TheTime->GetElapsedTime();

    level = lev;

    CubeTerrain::terrain = this;

    uint height = SegmentTerrain::HEIGHT;
    uint width = SegmentTerrain::WIDTH;

    uint segmentsInZ = level.Size() / height + ((level.Size() % height) == 0 ? 0 : 1);      // Сколько сегментов по иксу
    uint segmentsInX = level[0].Size() / width + ((level.Size() % width) == 0 ? 0 : 1);     // Сколько сегментов по зет

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
        uint i = row0 / height;

        segments[i].Resize(segmentsInX);

        for(uint col0 = 0; col0 < allCols; col0 += width)
        {
            uint numRows = (row0 + height > allRows) ? (allRows - row0) : height;
            uint numCols = (col0 + width > allCols) ? (allCols - col0) : width;

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

    URHO3D_LOGINFOF("time create terrain %f sec", TheTime->GetElapsedTime() - time);
}


void TerrainTV::SaveToFile(char * /*nameFile*/)
{

}


float TerrainTV::GetHeight(uint row, uint col)
{
    return level[row][col];
}


void TerrainTV::SetHeight(uint row, uint col, float height)
{
    level[row][col] = height;
}


void TerrainTV::Update()
{

}


uint TerrainTV::NumRows()
{
    return level.Size();
}


uint TerrainTV::NumCols()
{
    return level[0].Size();
}


bool TerrainTV::Empty()
{
    return level.Empty();
}


TPlane TerrainTV::GetIntersectionPlane(Ray& /*ray*/)
{
    return TPlane::ZERO;
}


Line TerrainTV::GetIntersectionEdge(Ray &/*ray*/)
{
    return Line::ZERO;
}


TPlane TerrainTV::GetPlane(uint /*row*/, uint /*col*/)
{
    return TPlane::ZERO;
}


Vector<Vector<float>> TerrainTV::GetMap()
{
    return level;
}


PODVector<CubeTerrain*>* TerrainTV::GetColumnCubes(const CubeTerrain *cube, DIR dir)
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


SegmentTerrain* TerrainTV::GetSegmentForCoord(uint row, uint col)
{
    return segments[row / SegmentTerrain::HEIGHT][col / SegmentTerrain::WIDTH];
}
