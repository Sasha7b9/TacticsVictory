#include <stdafx.h>


#include "CubeTerrain.h"
#include "Terrain.h"


Terrain* CubeTerrain::terrain = nullptr;


CubeTerrain::CubeTerrain(Context *context) :
    Object(context)
{
}

CubeTerrain::CubeTerrain(uint row, uint col, float height) :
    Object(gContext)
{
    this->row = row;
    this->col = col;

    underGround = height <= 0.0f;

    layer = (uint)fabs(height);
    if (!underGround)
    {
        layer--;
    }
}

void CubeTerrain::Create()
{
    CreateEdges();
    CreateSides();
}

void CubeTerrain::CreateEdges()
{
    CreateEdgeTop();
    CreateEdgeDown();
}

void CubeTerrain::CreateSides()
{
    CreateSideLeft();
    CreateSideTop();
    CreateSideRight();
    CreateSideDown();
}

void CubeTerrain::CreateEdgeTop()
{
    float z = underGround ? -(float)layer : (float)layer + 1.0f;

    EdgeCube &edge = edges[E_TOP];
    edge.exist = true;

    PointPlane &point0 = edge.plane.point[0];
    point0.coord = Vector3((float)col, z, -(float)row);
    point0.normal = Vector3::UP;
    point0.texCoord = Vector2::ZERO;

    PointPlane &point1 = edge.plane.point[1];
    point1.coord = Vector3((float)col + 1.0f, z, -(float)row);
    point1.normal = Vector3::UP;
    point1.texCoord = Vector2::UP;

    PointPlane &point2 = edge.plane.point[2];
    point2.coord = Vector3((float)col + 1.0f, z, -(float)row - 1.0f);
    point2.normal = Vector3::UP;
    point2.texCoord = Vector2::ONE;

    PointPlane &point3 = edge.plane.point[3];
    point3.coord = Vector3((float)col, z, -(float)row - 1.0f);
    point3.normal = Vector3::UP;
    point3.texCoord = Vector2::RIGHT;
}

void CubeTerrain::CreateEdgeDown()
{

}

void CubeTerrain::CreateSideLeft()
{
    SideCube &side = sides[S_LEFT];
    side.exist = true;

    PointPlane &point0 = side.plane.point[0];
    PointPlane &point1 = side.plane.point[1];
    PointPlane &point2 = side.plane.point[2];
    PointPlane &point3 = side.plane.point[3];

    PODVector<CubeTerrain*> *column = static_cast<Terrain*>(terrain)->GetColumnCubes(this, DIR_LEFT);

    if(!column)
    {
        return;
    }

    for(int i = (int)column->Size() - 1; i >= 0; i--)
    {
        
    }
}

void CubeTerrain::CreateSideTop()
{

}

void CubeTerrain::CreateSideRight()
{

}

void CubeTerrain::CreateSideDown()
{

}

void CubeTerrain::BuildVertexes(PODVector<float> &vertexes, PODVector<uint> &indexes)
{
    uint index = vertexes.Size() / 8;

    this->vertexes = &vertexes;

    if (edges[E_TOP].exist)
    {
        PlaneCube &plane = edges[E_TOP].plane;

        PushPoint(plane.point[0]);
        PushPoint(plane.point[1]);
        PushPoint(plane.point[2]);
        PushPoint(plane.point[3]);

        indexes.Push(index + 0);
        indexes.Push(index + 1);
        indexes.Push(index + 2);
        indexes.Push(index + 0);
        indexes.Push(index + 2);
        indexes.Push(index + 3);
    }
}

void CubeTerrain::PushPoint(PointPlane &point)
{
    vertexes->Push(point.coord.x_);
    vertexes->Push(point.coord.y_);
    vertexes->Push(point.coord.z_);

    vertexes->Push(point.normal.x_);
    vertexes->Push(point.normal.y_);
    vertexes->Push(point.normal.z_);

    vertexes->Push(point.texCoord.x_);
    vertexes->Push(point.texCoord.y_);
}
