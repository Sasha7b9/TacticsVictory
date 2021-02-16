/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include "stdafx.h"


SegmentTerrain::SegmentTerrain(Context *context) : Object(context)
{
    neighbours[LEFT] = neighbours[TOP] = neighbours[RIGHT] = neighbours[BOTTOM] = nullptr;
}


SegmentTerrain::~SegmentTerrain()
{
}


void SegmentTerrain::CreateFromVector(const Vector<Vector<float>> &level, uint row0, uint col0, uint numRows, uint numCols)
{
    float min = 1e10f;
    float max = -1e10f;

    for (uint row = row0; row < row0 + numRows; row++)
    {
        for (uint col = col0; col < col0 + numCols; col++)
        {
            float height = level[row][col];
            if(height < min)
            {
                min = height;
            }
            if(height > max)
            {
                max = height;
            }
        }
    }

    if(max > 0.0f)
    {
        ground.Resize((uint)(max));

        for (uint i = 0; i < ground.Size(); i++)
        {
            ground[i] = new LayerTerrain();
        }
    }


    if(min <= 0.0f)
    {
        underGround.Resize((uint)fabs(min) + 1);

        for (uint i = 0; i < underGround.Size(); i++)
        {
            underGround[i] = new LayerTerrain();
        }
    }

    for(uint row = row0; row < row0 + numRows; row++)
    {
        for(uint col = col0; col < col0 + numCols; col++)
        {
            SharedPtr<CubeTerrain> cube(new CubeTerrain(row, col, level[row][col]));
            AddCube(cube);
        }
    }

    CreateLayers();
}


void SegmentTerrain::AddCube(const SharedPtr<CubeTerrain> &cube)
{
    if(cube->underGround)
    {
        underGround[cube->layer]->AddCube(cube);
    }
    else
    {
        ground[cube->layer]->AddCube(cube);
    }
    TerrainTV::columnsCubes[cube->row][cube->col].Push(cube);
}


void SegmentTerrain::CreateLayers()
{
    for(auto & layer : ground)
    {
        layer->Create();
    }
    for(auto & layer : underGround)
    {
        layer->Create();
    }
}


void SegmentTerrain::Build()
{
    for(auto &layer : ground)
    {
        layer->Build();
    }
    for(auto &layer : underGround)
    {
        layer->Build();
    }
}


void SegmentTerrain::GetColumnCubes(uint row, uint col, PODVector<CubeTerrain*> &column)
{
    for(int i = (int)ground.Size() - 1; i >= 0; i--)
    {
        LayerTerrain *layer = ground[(uint)i];
        CubeTerrain* cube = layer->GetCube(row, col);
        if(cube)
        {
            column.Push(cube);
        }
    }

    for(int i = 0; i < (int)underGround.Size(); i++)
    {
        LayerTerrain *layer = underGround[(uint)i];
        CubeTerrain *cube = layer->GetCube(row, col);
        if(cube)
        {
            column.Push(cube);
        }
    }
}
