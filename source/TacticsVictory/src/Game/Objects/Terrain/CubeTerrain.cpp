#include <stdafx.h>


#include "CubeTerrain.h"
#include "Terrain.h"


TerrainRTS* CubeTerrain::terrain = nullptr;


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

#define GET_FOUR_POINTS_FOR_PLANE(pl)        \
    PointPlane &point0 = pl->plane.point[0]; \
    PointPlane &point1 = pl->plane.point[1]; \
    PointPlane &point2 = pl->plane.point[2]; \
    PointPlane &point3 = pl->plane.point[3];

#define CALCULATE_NORMALS                                                                       \
    point0.normal = (point1.coord - point0.coord).CrossProduct(point3.coord - point0.coord);    \
    point1.normal = (point2.coord - point1.coord).CrossProduct(point0.coord - point1.coord);    \
    point2.normal = (point3.coord - point2.coord).CrossProduct(point1.coord - point2.coord);    \
    point3.normal = (point0.coord - point3.coord).CrossProduct(point2.coord - point3.coord);


void CubeTerrain::CreateEdgeTop()
{
    float height = underGround ? -(float)layer : (float)layer + 1.0f;

    SharedPtr<EdgeCube> edge(new EdgeCube());
    edges[E_TOP] = edge;

    GET_FOUR_POINTS_FOR_PLANE(edge);

    point0.coord = Vector3((float)col, height, -(float)row);
    point0.texCoord = Vector2::ZERO;

    point1.coord = Vector3((float)col + 1.0f, height, -(float)row);
    point1.texCoord = Vector2::UP;

    point2.coord = Vector3((float)col + 1.0f, height, -(float)row - 1.0f);
    point2.texCoord = Vector2::ONE;

    point3.coord = Vector3((float)col, height, -(float)row - 1.0f);
    point3.texCoord = Vector2::RIGHT;

    CALCULATE_NORMALS
}

void CubeTerrain::CreateEdgeDown()
{

}

void CubeTerrain::CreateSideLeft()
{
    // Get the column of cubes, that are left of our. column[0] - min height
    PODVector<CubeTerrain*> *column = static_cast<TerrainRTS*>(terrain)->GetColumnCubes(this, DIR_LEFT);

    if(!column)
    {
        return;
    }

    for(int i = (int)column->Size() - 1; i >= 0; i--)
    {
        CubeTerrain *cube = (*column)[(uint)i];

        Vector3& coord = cube->GetEdgeCoord(E_TOP, C_TOPRIGHT);

        float heightLeftTopRight = coord.y_;

        if(heightLeftTopRight < GetEdgeCoord(E_TOP, C_TOPLEFT).y_)
        {
            SharedPtr<SideCube> side(new SideCube());
            sides[S_LEFT] = side;

            GET_FOUR_POINTS_FOR_PLANE(side);

            float height = underGround ? -(float)layer : (float)layer + 1.0f;

            point0.coord = Vector3((float)col, heightLeftTopRight, -(float)row);
            point0.texCoord = Vector2::ZERO;

            point1.coord = Vector3((float)col, height, -(float)row);
            point1.texCoord = Vector2::UP;

            point2.coord = Vector3((float)col, height, -(float)row - 1.0f);
            point2.texCoord = Vector2::ONE;

            point3.coord = Vector3((float)col, heightLeftTopRight, -(float)row - 1.0f);
            point3.texCoord = Vector2::RIGHT;

            CALCULATE_NORMALS

            break;
        }
    }
}

void CubeTerrain::CreateSideTop()
{
    // Get the column of cubes, that are top of our. column[0] - mini height
    PODVector<CubeTerrain*> *column = static_cast<TerrainRTS*>(terrain)->GetColumnCubes(this, DIR_TOP);

    if(!column)
    {
        return;
    }

    for(int i = (int)column->Size() - 1; i >= 0; i--)
    {
        CubeTerrain *cube = (*column)[(uint)i];

        Vector3& coord = cube->GetEdgeCoord(E_TOP, C_DOWNLEFT);

        float heightTopDownLeft = coord.y_;

        if(heightTopDownLeft < GetEdgeCoord(E_TOP, C_TOPLEFT).y_)
        {
            SharedPtr<SideCube> side(new SideCube());
            sides[S_TOP] = side;

            GET_FOUR_POINTS_FOR_PLANE(side);

            float height = underGround ? -(float)layer : (float)layer + 1.0f;

            point0.coord = Vector3((float)col, heightTopDownLeft, -(float)row);
            point0.texCoord = Vector2::ZERO;

            point1.coord = Vector3((float)col + 1.0f, heightTopDownLeft, -(float)row);
            point1.texCoord = Vector2::UP;

            point2.coord = Vector3((float)col + 1.0f, height, -(float)row);
            point2.texCoord = Vector2::ONE;

            point3.coord = Vector3((float)col, height, -(float)row);
            point3.texCoord = Vector2::RIGHT;

            CALCULATE_NORMALS

            break;
        }
    }
}

void CubeTerrain::CreateSideRight()
{
    PODVector<CubeTerrain*> *column = static_cast<TerrainRTS*>(terrain)->GetColumnCubes(this, DIR_RIGHT);

    if(!column)
    {
        return;
    }

    for(int i = (int)column->Size() - 1; i >= 0; i--)
    {
        CubeTerrain *cube = (*column)[(uint)i];
        
        Vector3& coord = cube->GetEdgeCoord(E_TOP, C_TOPRIGHT);

        float heightRightRightLeft = coord.y_;

        if(heightRightRightLeft < GetEdgeCoord(E_TOP, C_TOPRIGHT).y_)
        {
            SharedPtr<SideCube> side(new SideCube());
            sides[S_RIGHT] = side;

            GET_FOUR_POINTS_FOR_PLANE(side);

            float height = underGround ? -(float)layer : (float)layer + 1.0f;

            point0.coord = Vector3((float)col + 1.0f, height, -(float)row);
            point0.texCoord = Vector2::ZERO;

            point1.coord = Vector3((float)col + 1.0f, heightRightRightLeft, -(float)row);
            point1.texCoord = Vector2::UP;

            point2.coord = Vector3((float)col + 1.0f, heightRightRightLeft, -(float)row - 1.0f);
            point2.texCoord = Vector2::ONE;

            point3.coord = Vector3((float)col + 1.0f, height, -(float)row - 1.0f);
            point3.texCoord = Vector2::RIGHT;

            CALCULATE_NORMALS
        }
    }
}

void CubeTerrain::CreateSideDown()
{
    PODVector<CubeTerrain*> *column = static_cast<TerrainRTS*>(terrain)->GetColumnCubes(this, DIR_DOWN);

    if(!column)
    {
        return;
    }

    for(int i = (int)column->Size() - 1; i >= 0; i--)
    {
        CubeTerrain *cube = (*column)[(uint)i];

        Vector3& coord = cube->GetEdgeCoord(E_TOP, C_TOPLEFT);

        float heightDownTopLeft = coord.y_;

        if(heightDownTopLeft < GetEdgeCoord(E_TOP, C_DOWNLEFT).y_)
        {
            SharedPtr<SideCube> side(new SideCube());
            sides[S_DOWN] = side;

            GET_FOUR_POINTS_FOR_PLANE(side);

            float height = underGround ? -(float)layer : (float)layer + 1.0f;

            float z = -(float)(row + 1);

            point0.coord = Vector3((float)col, heightDownTopLeft, z);
            point0.texCoord = Vector2::ZERO;

            point1.coord = Vector3((float)col, height, z);
            point1.texCoord = Vector2::UP;

            point2.coord = Vector3((float)col + 1.0f, height, z);
            point2.texCoord = Vector2::ONE;

            point3.coord = Vector3((float)col + 1.0f, heightDownTopLeft, z);
            point3.texCoord = Vector2::RIGHT;

            CALCULATE_NORMALS
        }
    }
}

void CubeTerrain::BuildPlaneVerexes(PlaneCube &plane) 
{
    PushPoint(plane.point[0]);
    PushPoint(plane.point[1]);
    PushPoint(plane.point[2]);
    PushPoint(plane.point[3]);

    uint index = vertexes->Size() / 8;

    indexes->Push(index + 0);
    indexes->Push(index + 1);
    indexes->Push(index + 2);
    indexes->Push(index + 0);
    indexes->Push(index + 2);
    indexes->Push(index + 3);
}

void CubeTerrain::BuildVertexes(PODVector<float> &vertexes, PODVector<uint> &indexes)
{
    this->vertexes = &vertexes;
    this->indexes = &indexes;

    if (edges[E_TOP])
    {
        BuildPlaneVerexes(edges[E_TOP]->plane);
    }

    if(edges[E_DOWN])
    {
        BuildPlaneVerexes(edges[E_DOWN]->plane);
    }

    if(sides[S_LEFT])
    {
        BuildPlaneVerexes(sides[S_LEFT]->plane);
    }

    if(sides[S_TOP])
    {
        BuildPlaneVerexes(sides[S_TOP]->plane);
    }

    if(sides[S_RIGHT])
    {
        BuildPlaneVerexes(sides[S_RIGHT]->plane);
    }

    if(sides[S_DOWN])
    {
        BuildPlaneVerexes(sides[S_DOWN]->plane);
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

Vector3& CubeTerrain::GetEdgeCoord(EDGE edge, CORNER corner)
{
    if(edge == E_TOP && edges[E_TOP] == 0)
    {
        CreateEdgeTop();
    }
    return edges[edge]->plane.point[corner].coord;
}
