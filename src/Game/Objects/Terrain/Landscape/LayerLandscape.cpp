#include <stdafx.h>


#include "LayerLandscape.h"


LayerLandscape::LayerLandscape(Context *context) :
    Object(context)
{

}

void LayerLandscape::AddCube(SharedPtr<CubeLandscape> &cube)
{
    cubes.Push(cube);
}

void LayerLandscape::Create()
{
    for(auto &cube : cubes)
    {
        cube->Create();
    }
}

void LayerLandscape::Build()
{
    PODVector<float> vertexes;
    PODVector<uint> indexes;

    uint index = vertexes.Size() / 8;

    for(auto & cube : cubes)
    {
        PlaneCube &plane = cube->edges[E_TOP]->plane;

        PushPoint(vertexes, plane.point[0]);
        PushPoint(vertexes, plane.point[1]);
        PushPoint(vertexes, plane.point[2]);
        PushPoint(vertexes, plane.point[3]);

        indexes.Push(index + 0U);
        indexes.Push(index + 1U);
        indexes.Push(index + 2U);
        indexes.Push(index + 0U);
        indexes.Push(index + 2U);
        indexes.Push(index + 3U);
    }
}

void LayerLandscape::PushPoint(PODVector<float> &vertexes, PointPlane &point)
{
    vertexes.Push(point.coord.x_);
    vertexes.Push(point.coord.y_);
    vertexes.Push(point.coord.z_);

    vertexes.Push(point.normal.x_);
    vertexes.Push(point.normal.y_);
    vertexes.Push(point.normal.z_);

    vertexes.Push(point.texCoord.x_);
    vertexes.Push(point.texCoord.y_);
}
