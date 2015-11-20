#include <stdafx.h>


#include "SegmentLandscape.h"


SegmentLandscape::SegmentLandscape(Context *context) :
    Object(context)
{

}

SegmentLandscape::~SegmentLandscape()
{

}

void SegmentLandscape::CreateFromVector(Vector<Vector<float>> &level)
{
    //uint numRows = level.Size();
    //uint numCols = level[0].Size();
    uint numRows = 50;
    uint numCols = 50;

    float min = 1e10f;
    float max = -1e10f;

    for (uint row = 0; row < numRows; row++)
    {
        for (uint col = 0; col < numCols; col++)
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
            ground[i] = new LayerLandscape();
        }
    }

    

    if(min <= 0.0f)
    {
        underGround.Resize((uint)fabs(min) + 1);

        for (uint i = 0; i < underGround.Size(); i++)
        {
            underGround[i] = new LayerLandscape();
        }
    }

    for(uint row = 0; row < numRows; row++)
    {
        for(uint col = 0; col < numCols; col++)
        {
            SharedPtr<CubeLandscape> cube(new CubeLandscape(row, col, level[row][col]));
            AddCube(cube);
        }
    }

    CreateLayers();

    Build();
}

void SegmentLandscape::AddCube(SharedPtr<CubeLandscape> &cube)
{
    if(cube->underGround)
    {
        underGround[cube->layer]->AddCube(cube);
    }
    else
    {
        ground[cube->layer]->AddCube(cube);
    }
}

void SegmentLandscape::CreateLayers()
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

void SegmentLandscape::Build()
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

void SegmentLandscape::SaveToFile(char * /*nameFile*/)
{

}
