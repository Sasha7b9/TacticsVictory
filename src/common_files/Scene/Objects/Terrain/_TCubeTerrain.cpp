/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include "stdafx.h"
#include "Scene/Objects/Terrain/_TEdgeCube.h"
#include "Scene/Objects/Terrain/_TSideCube.h"


TTerrain* CubeTerrain::terrain = nullptr;


CubeTerrain::CubeTerrain(Context *context) : Object(context)
{
}


CubeTerrain::CubeTerrain(uint row, uint col, float height) :
    Object(TheContext)
{
    this->row = row;
    this->col = col;

    underGround = (height <= 0.0f);

    layer = static_cast<uint>(fabs(height));
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


#define GET_FOUR_POINTS_FOR_PLANE(pl)       \
    PlaneCube &plane = pl->plane;           \
    PointPlane &point0 = plane.point[0];    \
    PointPlane &point1 = plane.point[1];    \
    PointPlane &point2 = plane.point[2];    \
    PointPlane &point3 = plane.point[3];

#define CALCULATE_NORMALS                                                                       \
    point0.normal = (point1.coord - point0.coord).CrossProduct(point3.coord - point0.coord);    \
    point1.normal = (point2.coord - point1.coord).CrossProduct(point0.coord - point1.coord);    \
    point2.normal = (point3.coord - point2.coord).CrossProduct(point1.coord - point2.coord);    \
    point3.normal = (point0.coord - point3.coord).CrossProduct(point2.coord - point3.coord);


void CubeTerrain::CreateEdgeTop()
{
    float height = underGround ? - static_cast<float>(layer) : static_cast<float>(layer) + 1.0f;

    SharedPtr<EdgeCube> edge(new EdgeCube());
    edges[E_TOP] = edge;

    GET_FOUR_POINTS_FOR_PLANE(edge);

    point3.coord = Vector3(static_cast<float>(row), height, static_cast<float>(col));
    point3.texCoord = Vector2::ZERO;

    point2.coord = Vector3(static_cast<float>(row) + 1.0f, height, static_cast<float>(col));
    point2.texCoord = Vector2::UP;

    point1.coord = Vector3(static_cast<float>(row) + 1.0f, height, static_cast<float>(col) + 1.0f);
    point1.texCoord = Vector2::ONE;

    point0.coord = Vector3(static_cast<float>(row), height, static_cast<float>(col) + 1.0f);
    point0.texCoord = Vector2::RIGHT;

    CALCULATE_NORMALS
}


void CubeTerrain::CreateEdgeDown()
{

}


void CubeTerrain::CreateSideLeft()
{
    // Получим столбик кубов, находящихс слева от нашего. column[0] имеет минимальную высоту

    PODVector<CubeTerrain*> *column = static_cast<TTerrain*>(terrain)->GetColumnCubes(this, DIR::LEFT);

    float height = 0.0f;

    if(column)                                                          // Если слева от нашей клетки есть другие
    {
        for(int i = static_cast<int>(column->Size()) - 1; i >= 0; i--)
        {
            CubeTerrain *cube = (*column)[(uint)i];

            Vector3& coord = cube->GetEdgeCoord(E_TOP, C_TOPRIGHT);     // Получаем координату верхнего правого угла суба, который находится слева

            if(coord.y_ < GetEdgeCoord(E_TOP, C_TOPLEFT).y_)
            {
                height = coord.y_;
                break;
            }
        }
    }

    sides[S_LEFT] = CreateSide(S_LEFT, height);
}


void CubeTerrain::CreateSideTop()
{
    // Get the column of cubes, that are top of our. column[0] - mini height

    // Получем столбик кубов, находящихся вверху нашего. column[0] имеет минимальную высоту
    PODVector<CubeTerrain*> *column = static_cast<TTerrain*>(terrain)->GetColumnCubes(this, DIR::TOP);

    float height = 0.0f;

    if(column)
    {
        for(int i = static_cast<int>(column->Size()) - 1; i >= 0; i--)
        {
            CubeTerrain *cube = (*column)[(uint)i];

            Vector3& coord = cube->GetEdgeCoord(E_TOP, C_DOWNLEFT);

            if(coord.y_ < GetEdgeCoord(E_TOP, C_TOPLEFT).y_)
            {
                height = coord.y_;
                break;
            }
        }
    }

    sides[S_TOP] = CreateSide(S_TOP, height);
}


void CubeTerrain::CreateSideRight()
{
    PODVector<CubeTerrain*> *column = static_cast<TTerrain*>(terrain)->GetColumnCubes(this, DIR::RIGHT);

    float height = 0.0f;

    if(column)
    {
        for(int i = static_cast<int>(column->Size()) - 1; i >= 0; i--)
        {
            CubeTerrain *cube = (*column)[(uint)i];

            Vector3& coord = cube->GetEdgeCoord(E_TOP, C_TOPRIGHT);

            if(coord.y_ < GetEdgeCoord(E_TOP, C_TOPRIGHT).y_)
            {
                height = coord.y_;
                break;
            }
        }
    }

    sides[S_RIGHT] = CreateSide(S_RIGHT, height);
}


void CubeTerrain::CreateSideDown()
{
    PODVector<CubeTerrain*> *column = static_cast<TTerrain*>(terrain)->GetColumnCubes(this, DIR::DOWN);

    float height = 0.0f;

    if(column)
    {
        for(int i = static_cast<int>(column->Size()) - 1; i >= 0; i--)
        {
            CubeTerrain *cube = (*column)[(uint)i];

            Vector3& coord = cube->GetEdgeCoord(E_TOP, C_TOPLEFT);

            if(coord.y_ < GetEdgeCoord(E_TOP, C_DOWNLEFT).y_)
            {
                height = coord.y_;
                break;
            }
        }
    }

    sides[S_DOWN] = CreateSide(S_DOWN, height);
}


SharedPtr<SideCube> CubeTerrain::CreateSide(SIDE side, float anotherHeight)
{
    const float height = underGround ? -static_cast<float>(layer) : static_cast<float>(layer) + 1.0f;

    const float dX[4][4] =
    {
        {0.0f, 0.0f, 1.0f, 1.0f},

        {0.0f, 0.0f, 0.0f, 0.0f},

        {1.0f, 1.0f, 0.0f, 0.0f},

        {1.0f, 1.0f, 1.0f, 1.0f}
    };

    const float dY[4][4] =
    {
        {anotherHeight, height, height, anotherHeight},
        {anotherHeight, anotherHeight, height, height},
        {anotherHeight, height, height, anotherHeight},
        {height, height, anotherHeight, anotherHeight}
    };

    const float dZ[4][4] =
    {
        {0.0f, 0.0f, 0.0f, 0.0f},

        {0.0f, 1.0f, 1.0f, 0.0f},

        {1.0f, 1.0f, 1.0f, 1.0f},

        {0.0f, 1.0f, 1.0f, 0.0f}
    };

    SharedPtr<SideCube> retValue(new SideCube());

    GET_FOUR_POINTS_FOR_PLANE(retValue);

    point0.coord = Vector3(static_cast<float>(row) + dX[side][0], dY[side][0], static_cast<float>(col) + dZ[side][0]);
    point0.texCoord = Vector2::ZERO;

    point1.coord = Vector3(static_cast<float>(row) + dX[side][1], dY[side][1], static_cast<float>(col) + dZ[side][1]);
    point1.texCoord = Vector2::UP;

    point2.coord = Vector3(static_cast<float>(row) + dX[side][2], dY[side][2], static_cast<float>(col) + dZ[side][2]);
    point2.texCoord = Vector2::ONE;

    point3.coord = Vector3(static_cast<float>(row) + dX[side][3], dY[side][3], static_cast<float>(col) + dZ[side][3]);
    point3.texCoord = Vector2::RIGHT;

    CALCULATE_NORMALS;

    return retValue;
}


void CubeTerrain::BuildPlaneVerexes(const PlaneCube &plane) 
{
    uint index = vertexes->Size() / 8;

    PushPoint(plane.point[0]);
    PushPoint(plane.point[1]);
    PushPoint(plane.point[2]);
    PushPoint(plane.point[3]);

    indexes->Push(index + 0); //-V525
    indexes->Push(index + 1);
    indexes->Push(index + 2);
    indexes->Push(index + 0);
    indexes->Push(index + 2);
    indexes->Push(index + 3);
}


void CubeTerrain::BuildVertexes(PODVector<float> &v, PODVector<uint> &i)
{
    vertexes = &v;
    indexes = &i;

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


void CubeTerrain::PushPoint(const PointPlane &point)
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
    return edges[edge]->plane.point[(uint64)corner].coord;
}
