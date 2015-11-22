#include <stdafx.h>


#include "CubeTerrain.h"


CubeTerrain::CubeTerrain(Context *context) :
    Object(context)
{
    Init();
}

CubeTerrain::CubeTerrain(uint row, uint col, float height) :
    Object(gContext)
{
    Init();

    this->row = row;
    this->col = col;

    underGround = height <= 0.0f;

    layer = (uint)fabs(height);
    if (!underGround)
    {
        layer--;
    }
}

void CubeTerrain::Init()
{
    for(auto &side : sides)
    {
        side = nullptr;
    }
    for(auto &corner : corners)
    {
        corner = nullptr;
    }
    for(auto &edge : edges)
    {
        edge = nullptr;
    }
}

void CubeTerrain::Create()
{
    CreateEdges();
}

void CubeTerrain::CreateEdges()
{
    CreateEdgeTop();
    CreateEdgeDown();
}

void CubeTerrain::CreateEdgeTop()
{
    SharedPtr<EdgeCube> edge(new EdgeCube());

    edges[E_TOP] = edge;

    float z = underGround ? -(float)layer : (float)layer + 1.0f;

    PointPlane &point0 = edge->plane.point[0];
    point0.coord = Vector3((float)col, z, -(float)row);
    point0.normal = Vector3::UP;
    point0.texCoord = Vector2::ZERO;

    PointPlane &point1 = edge->plane.point[1];
    point1.coord = Vector3((float)col + 1.0f, z, -(float)row);
    point1.normal = Vector3::UP;
    point1.texCoord = Vector2::UP;

    PointPlane &point2 = edge->plane.point[2];
    point2.coord = Vector3((float)col + 1.0f, z, -(float)row - 1.0f);
    point2.normal = Vector3::UP;
    point2.texCoord = Vector2::ONE;

    PointPlane &point3 = edge->plane.point[3];
    point3.coord = Vector3((float)col, z, -(float)row - 1.0f);
    point3.normal = Vector3::UP;
    point3.texCoord = Vector2::RIGHT;
}

void CubeTerrain::CreateEdgeDown()
{

}

void CubeTerrain::BuildVertexes()
{
    uint index = vertexes.Size() / 8;

    if (edges[E_TOP])
    {
        PlaneCube &plane = edges[E_TOP]->plane;

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

void CubeTerrain::PushPoint(PODVector<float> &vertexes, PointPlane &point)
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
