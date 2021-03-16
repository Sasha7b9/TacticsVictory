// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Core/Math_.h"
#include "Scene/Scene_.h"
#include "Scene/Terrain/CubeTerrain_.h"
#include "Scene/Terrain/LayerTerrain_.h"


LayerTerrain::LayerTerrain() : Object(TheContext)
{

}


LayerTerrain::~LayerTerrain()
{
}


void LayerTerrain::AddCube(const SharedPtr<CubeTerrain> &cube)
{
    cubes.Push(cube);
}


void LayerTerrain::Create()
{
    for(auto cube : cubes)
    {
        cube->Create();
    }
}


CubeTerrain* LayerTerrain::GetCube(uint row, uint col)
{
    for(auto cube : cubes)
    {
        if(cube->row == row && cube->col == col)
        {
            return cube;
        }
    }

    return nullptr;
}
