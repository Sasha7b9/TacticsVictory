#include <stdafx.h>


#include "Landscape.h"


Landscape::Landscape(Context *context) :
    Object(context)
{

}

Landscape::~Landscape()
{

}

void Landscape::CreateFromVector(Vector<Vector<float>> &level)
{
    uint numRows = level.Size();
    uint numCols = level[0].Size();

    float min = 1e10f;
    float max = -1e10f;
    
    for(auto &row : level)
    {
        for(float helght : row)
        {
            if(helght < min)
            {
                min = helght;
            }
            if(helght > max)
            {
                max = helght;
            }
        }
    }

    if(max > 0.0f)
    {
        underGround.Resize((uint)(max)+1);
    }

    if(min <= 0.0f)
    {
        ground.Resize((uint)fabs(min) + 1);
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

void Landscape::AddCube(SharedPtr<CubeLandscape> &cube)
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

void Landscape::CreateLayers()
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

void Landscape::Build()
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

void Landscape::SaveToFile(char *nameFile)
{

}
