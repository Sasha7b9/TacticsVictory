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
    URHO3D_LOGINFOF("1 %f", gTime->GetElapsedTime());
    //uint numRows = level.Size();
    //uint numCols = level[0].Size();
    uint numRows = 5;
    uint numCols = 5;

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

        for (uint i = 0; i < underGround.Size(); i++)
        {
            ground[i] = new LayerLandscape();
        }
    }

    

    if(min <= 0.0f)
    {
        underGround.Resize((uint)fabs(min) + 1);

        for (uint i = 0; i < ground.Size(); i++)
        {
            underGround[i] = new LayerLandscape();
        }
    }

    uint sizeGround = ground.Size();
    uint sizeUnderGround = underGround.Size();

    for(uint row = 0; row < numRows; row++)
    {
        for(uint col = 0; col < numCols; col++)
        {
            SharedPtr<CubeLandscape> cube(new CubeLandscape(row, col, level[row][col]));
            AddCube(cube);
        }
    }

    URHO3D_LOGINFOF("2 %f", gTime->GetElapsedTime());

    CreateLayers();

    URHO3D_LOGINFOF("3 %f", gTime->GetElapsedTime());

    Build();

    URHO3D_LOGINFOF("4 %f", gTime->GetElapsedTime());
}

void Landscape::AddCube(SharedPtr<CubeLandscape> &cube)
{
    if(cube->underGround)
    {
        uint size = underGround.Size();
        underGround[cube->layer]->AddCube(cube);
    }
    else
    {
        uint layer = cube->layer;
        uint size = ground.Size();
        ground[layer]->AddCube(cube);
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
