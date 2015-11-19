#include <stdafx.h>


#include "CubeLandscape.h"


CubeLandscape::CubeLandscape(Context *context) :
    Object(context)
{
    Init();
}

CubeLandscape::CubeLandscape(uint row, uint col, float height) :
    Object(gContext)
{
    Init();

    this->row = row;
    this->col = col;

    layer = (uint)fabs(height);

    underGround = (height <= 0.0f) ? true : false;
}

void CubeLandscape::Init()
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

void CubeLandscape::Create()
{
    CreateEdges();
}

void CubeLandscape::CreateEdges()
{
    CreateEdgeTop();
    CreateEdgeDown();
}

void CubeLandscape::CreateEdgeTop()
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

void CubeLandscape::CreateEdgeDown()
{

}
