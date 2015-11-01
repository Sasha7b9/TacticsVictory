#include <stdafx.h>


#include "TerrainSegment.h"
#include "Core/Math.h"
#include "Graphics/Objects/Plane.h"
#include "Graphics/Objects/Triangle.h"


using Urho3D::C_TOPLEFT;
using Urho3D::C_TOPRIGHT;
using Urho3D::C_BOTTOMRIGHT;
using Urho3D::C_BOTTOMLEFT;


lTerrainSegment::lTerrainSegment(Vector<Vector<float>> &eMap, const Vector3 &shift_) :
    Object(gContext),
    shift(shift_)
{
    PrepareHashMaps();

    vb = new VertexBuffer(gContext);
    ib = new IndexBuffer(gContext);
    geometry = new Geometry(gContext);
    model = new Model(gContext);
    node = gScene->CreateChild(NODE_TERRAIN);
    object = node->CreateComponent<StaticModel>();

    Rebuild(eMap);
}

void lTerrainSegment::Clear()
{
    gScene->RemoveChild(node);
}

void lTerrainSegment::Rebuild(Vector<Vector<float>> &map_)
{
    SAFE_DELETE_ARRAY(bufVert);
    SAFE_DELETE_ARRAY(bufInd);

    map = map_;

    widthMap = map[0].Size();
    heightMap = map.Size();

    vertexes.Clear();
    indexes.Clear();
    bufIndPlanes.Clear();
    bufIndClosingTriangles.Clear();

    for(uint row = 1; row < heightMap - 1; row++)
    {
        for(uint col = 1; col < widthMap - 1; col++)
        {
            AddPlaneWithSubplanes(row, col);
        }
    }

    numVert = vertexes.Size();
    bufVert = new float[numVert];
    numInd = indexes.Size();
    bufInd = new uint[numInd];

    for(uint i = 0; i < vertexes.Size(); i++)
    {
        bufVert[i] = vertexes[i];
    }

    for(uint i = 0; i < indexes.Size(); i++)
    {
        bufInd[i] = indexes[i];
    }

    vb->SetShadowed(true);
    vb->SetSize(vertexes.Size() / 8, Urho3D::MASK_POSITION | Urho3D::MASK_NORMAL | Urho3D::MASK_TEXCOORD1);
    vb->SetData(bufVert);

    ib->SetShadowed(true);
    ib->SetSize(indexes.Size(), true);
    ib->SetData(bufInd);

    
    geometry->SetVertexBuffer(0, vb);
    geometry->SetIndexBuffer(ib);
    geometry->SetDrawRange(Urho3D::TRIANGLE_LIST, 0, ib->GetIndexCount());

    vbVector.Clear();
    ibVector.Clear();

    vbVector.Push(vb);
    ibVector.Push(ib);
    model->SetNumGeometries(1);
    model->SetNumGeometryLodLevels(0, 1);
    model->SetGeometry(0, 0, geometry);

    model->SetVertexBuffers(vbVector, morpRange, morpRange);
    model->SetIndexBuffers(ibVector);

    model->SetBoundingBox(BoundingBox(Vector3(-1000.0f, -1000.0f, -1000.0f), Vector3(1000.0f, 1000.0f, 1000.0f)));

    if(!object->GetModel())
    {
        object->SetModel(model);
        object->SetMaterial(gCache->GetResource<Material>("Materials/TVTerrain.xml"));
        object->SetCastShadows(true);
    }

    // Подключим к физике
    //node->CreateComponent<RigidBody>();
    //CollisionShape *shape = node->CreateComponent<CollisionShape>();
    //shape->SetTriangleMesh(model);
    //shape->SetBox({-100.0f, -1.0f, -100.0f}, {100.0f, 1.0f, 100.0f});

    CalculateBoundingBox();
}

lTerrainSegment::~lTerrainSegment()
{
    SAFE_DELETE_ARRAY(bufVert);
    SAFE_DELETE_ARRAY(bufInd);
}

void lTerrainSegment::PushNormal(const Vector3 &normal)
{
    vertexes.Push(normal.x_);
    vertexes.Push(normal.y_);
    vertexes.Push(normal.z_);
}

void lTerrainSegment::PushCoord(const Vector3 &coord)
{
    vertexes.Push(coord.x_ + shift.x_);
    vertexes.Push(coord.y_ + shift.y_);
    vertexes.Push(coord.z_ + shift.z_);
}

void lTerrainSegment::PushTexCoord(float x, float y)
{
    vertexes.Push(x);
    vertexes.Push(y);
}

void lTerrainSegment::AddPlane(const Vector3 &p0, const Vector3 &p1, const Vector3 &p2, const Vector3 &p3, float dTex)
{
    uint startIndex = vertexes.Size() / 8;

    PushCoord(p0);
    PushNormal((p1 - p0).CrossProduct(p2 - p0));
    PushTexCoord(0.0f, 0.0f);

    PushCoord(p1);
    PushNormal((p2 - p1).CrossProduct(p0 - p1));
    PushTexCoord(0.0f, dTex < 0.0f ? -dTex : 1.0f);

    PushCoord(p2);
    PushNormal((p0 - p2).CrossProduct(p1 - p2));
    PushTexCoord(dTex < 0.0f ? 1.0f : dTex, dTex < 0.0f ? -dTex : 1.0f);

    PushCoord(p3);
    PushNormal((p0 - p3).CrossProduct(p2 - p3));
    PushTexCoord(dTex < 0.0f ? 1.0f : dTex, 0.0f);

    indexes.Push(startIndex + 2U);
    indexes.Push(startIndex + 0U);
    indexes.Push(startIndex + 1U);
    indexes.Push(startIndex + 0U);
    indexes.Push(startIndex + 2U);
    indexes.Push(startIndex + 3U);

    if(p0.y_ == p1.y_ && p1.y_ == p2.y_ && p2.y_ == p3.y_)
    {
        bufIndPlanes.Push(startIndex + 0U);
        bufIndPlanes.Push(startIndex + 1U);
        bufIndPlanes.Push(startIndex + 2U);
        bufIndPlanes.Push(startIndex + 3U);
    }
    else
    {
        bufIndClosingTriangles.Push(startIndex + 2U);
        bufIndClosingTriangles.Push(startIndex + 0U);
        bufIndClosingTriangles.Push(startIndex + 1U);
        bufIndClosingTriangles.Push(startIndex + 0U);
        bufIndClosingTriangles.Push(startIndex + 2U);
        bufIndClosingTriangles.Push(startIndex + 3U);
    }
}

void lTerrainSegment::AddTriangle(const Vector3 &p0, const Vector3 &p1, const Vector3 &p2, float dTex)
{
    if(p0 == p1 || p1 == p2 || p2 == p0)
    {
        return;
    }

    uint startIndex = vertexes.Size() / 8;

    PushCoord(p0);
    PushNormal((p1 - p0).CrossProduct(p2 - p0));
    PushTexCoord(0.0f, 0.0f);

    PushCoord(p1);
    PushNormal((p2 - p1).CrossProduct(p0 - p1));
    PushTexCoord(0.0f, dTex < 0.0f ? -dTex : 1.0f);

    PushCoord(p2);
    PushNormal((p0 - p2).CrossProduct(p1 - p2));
    PushTexCoord(dTex < 0.0f ? 1.0f : dTex, dTex < 0.0f ? -dTex : 1.0f);

    indexes.Push(startIndex + 2U);
    indexes.Push(startIndex + 0U);
    indexes.Push(startIndex + 1U);

    bufIndClosingTriangles.Push(startIndex + 2U);
    bufIndClosingTriangles.Push(startIndex + 0U);
    bufIndClosingTriangles.Push(startIndex + 1U);
}

void lTerrainSegment::Add2Plane(const Vector3 &p0, const Vector3 &p1, const Vector3 &p2, const Vector3 &p3)
{
    float delta = fabs(p0.y_ - p2.y_);

    AddPlane(p0, p1, p2, p3, delta == 0.0f ? 1.0f : delta);
    //AddPlane(p0, p3, p2, p1, delta == 0.0f ? 1.0f : -delta);
}

void lTerrainSegment::AddPlaneWithSubplanes(uint row, uint col)
{
    Add2Plane(CoordCorner(row, col, C_TOPLEFT), CoordCorner(row, col, C_TOPRIGHT), CoordCorner(row, col, C_BOTTOMRIGHT), CoordCorner(row, col, C_BOTTOMLEFT));

    if(row > 0)
    {
        AddSidePlane(row, col, DIR_UP);
    }
    if(col > 0)
    {
        AddSidePlane(row, col, DIR_LEFT);
    }
    if(row > 0 && col > 0)
    {
        AddTopLeftCornerPlanes(row, col);
    }
}

lPlane lTerrainSegment::GetPlane(uint row, uint col)
{
    lPlane plane;

    //  + Vector3(-1.0f, 0.0f, 1.0f)
    plane.v0 = CoordCorner(row + 1, col + 1, C_TOPLEFT) + shift;
    plane.v1 = CoordCorner(row + 1, col + 1, C_TOPRIGHT) + shift;
    plane.v2 = CoordCorner(row + 1, col + 1, C_BOTTOMRIGHT) + shift;
    plane.v3 = CoordCorner(row + 1, col + 1, C_BOTTOMLEFT) + shift;

    return plane;
}

float lTerrainSegment::HeightCell(uint row, uint col)
{
    return (float)map[row][col];
}

void lTerrainSegment::AddSidePlane(uint row, uint col, Direction dir)
{
    if(dir == DIR_UP)
    {
        if(HeightCell(row, col) != HeightCell(row - 1, col))
        {
            AddUpPlane(row, col);
        }
    }
    else if(dir == DIR_LEFT)
    {
        if(HeightCell(row, col) != HeightCell(row, col - 1))
        {
            AddLeftPlane(row, col);
        }
    }
}

void lTerrainSegment::AddUpPlane(uint row, uint col)
{
    Add2Plane(CoordCorner(row - 1, col, C_BOTTOMLEFT), CoordCorner(row - 1, col, C_BOTTOMRIGHT), CoordCorner(row, col, C_TOPRIGHT), CoordCorner(row, col, C_TOPLEFT));
}

void lTerrainSegment::AddLeftPlane(uint row, uint col)
{
    Add2Plane(CoordCorner(row, col - 1, C_BOTTOMRIGHT), CoordCorner(row, col - 1, C_TOPRIGHT), CoordCorner(row, col, C_TOPLEFT), CoordCorner(row, col, C_BOTTOMLEFT));
}

#define PUSH_TOP_LEFT(d0, d1, d2, dX, dZ) mapTopLeft[MapPlaneKey(d0, d1, d2)] = MapPlaneValue(dX, dZ);
#define PUSH_TOP_RIGHT(d0, d1, d2, dX, dZ) mapTopRight[MapPlaneKey(d0, d1, d2)] = MapPlaneValue(dX, dZ);
#define PUSH_BTM_RIGHT(d0, d1, d2, dX, dZ) mapBtmRight[MapPlaneKey(d0, d1, d2)] = MapPlaneValue(dX, dZ);
#define PUSH_BTM_LEFT(d0, d1, d2, dX, dZ) mapBtmLeft[MapPlaneKey(d0, d1, d2)] = MapPlaneValue(dX, dZ);

#define PUSH_CORNER(dLeft, dTopLeft, dTop, dDiagLeft, dDiagTop, dRow00, dCol00, cor00, dRow01, dCol01, cor01) \
    mapCornerTopLeft[MapCornerKey(dLeft, dTopLeft, dTop, dDiagLeft, dDiagTop)] = MapCornerValue(dRow00, dCol00, cor00, dRow01, dCol01, cor01);

#define PUSH_CORNERS(dLeft, dTopLeft, dTop, dDiagLeft, dDiagTop, dRow00, dCol00, cor00, dRow01, dCol01, cor01, dRow10, dCol10, cor10, dRow11, dCol11, cor11) \
    mapCornerTopLeft[MapCornerKey(dLeft, dTopLeft, dTop, dDiagLeft, dDiagTop)] = MapCornerValue(dRow00, dCol00, cor00, dRow01, dCol01, cor01, dRow10, dCol10, cor10, dRow11, dCol11, cor11);

#define PUSH_CORNERS2(dLeft, dTopLeft, dTop, dDiagLeft, dDiagTop, dRow00, dCol00, cor00, dRow01, dCol01, cor01, dRow10, dCol10, cor10, dRow11, dCol11, cor11, dRow12, dCol12, cor12) \
    mapCornerTopLeft[MapCornerKey(dLeft, dTopLeft, dTop, dDiagLeft, dDiagTop)] = MapCornerValue(dRow00, dCol00, cor00, dRow01, dCol01, cor01, dRow10, dCol10, cor10, dRow11, dCol11, cor11, dRow12, dCol12, cor12);

void lTerrainSegment::PrepareHashMaps()
{
    const float delta = 0.1f;
    bool jumper = false;
    bool smoothing = true;

    PUSH_TOP_LEFT(-1, -1, -1, smoothing ? delta : 0, delta);
    PUSH_TOP_LEFT(0, -1, -1, 0, delta);
    PUSH_TOP_LEFT(0, 0, 1, -delta, delta);
    PUSH_TOP_LEFT(-1, -1, 0, delta, 0);
    PUSH_TOP_LEFT(0, 1, 0, delta, delta);
    PUSH_TOP_LEFT(1, 0, 0, delta, -delta);
    PUSH_TOP_LEFT(1, 1, 0, delta, 0);
    PUSH_TOP_LEFT(0, 1, 1, 0, delta);

    PUSH_TOP_LEFT(1, 1, 1, delta, delta);
    PUSH_TOP_LEFT(-1, 0, 0, delta, -delta);
    PUSH_TOP_LEFT(0, -1, 0, delta, delta);
    PUSH_TOP_LEFT(0, 0, -1, -delta, delta);
    PUSH_TOP_LEFT(-1, -1, 1, delta, delta);
    PUSH_TOP_LEFT(-1, 0, 1, delta, delta);
    PUSH_TOP_LEFT(0, 1, -1, 0, delta);
    PUSH_TOP_LEFT(0, -1, 1, 0, delta);
    PUSH_TOP_LEFT(1, -1, -1, delta, delta);
    PUSH_TOP_LEFT(-1, 1, 1, delta, delta);
    PUSH_TOP_LEFT(1, 1, -1, delta, delta);
    PUSH_TOP_LEFT(1, -1, 1, delta, delta);
    PUSH_TOP_LEFT(-1, 0, -1, delta, delta);
    PUSH_TOP_LEFT(-1, 1, -1, delta, delta);
    PUSH_TOP_LEFT(-1, 1, 0, delta, 0);
    PUSH_TOP_LEFT(1, -1, 0, delta, 0);
    PUSH_TOP_LEFT(1, 0, 1, delta, delta);
    PUSH_TOP_LEFT(1, 0, -1, delta, delta);

    PUSH_TOP_RIGHT(-1, -1, -1, -delta, delta);
    PUSH_TOP_RIGHT(0, 1, 0, -delta, delta);
    PUSH_TOP_RIGHT(1, 0, 0, delta, delta);
    PUSH_TOP_RIGHT(0, 0, 1, -delta, -delta);
    PUSH_TOP_RIGHT(0, -1, -1, -delta, 0);
    PUSH_TOP_RIGHT(0, 1, 1, -delta, 0);
    PUSH_TOP_RIGHT(1, 1, 0, 0, delta);
    PUSH_TOP_RIGHT(-1, -1, 0, 0, delta);

    PUSH_TOP_RIGHT(1, 0, 1, -delta, delta);
    PUSH_TOP_RIGHT(1, -1, -1, -delta, delta);
    PUSH_TOP_RIGHT(1, 1, -1, -delta, delta);
    PUSH_TOP_RIGHT(-1, -1, 1, smoothing ? -delta : 0, delta);
    PUSH_TOP_RIGHT(1, 1, 1, -delta, delta);
    PUSH_TOP_RIGHT(-1, 0, 0, delta, delta);
    PUSH_TOP_RIGHT(0, 0, -1, -delta, -delta);
    PUSH_TOP_RIGHT(0, -1, 0, -delta, delta);
    PUSH_TOP_RIGHT(-1, 1, 1, -delta, delta);
    PUSH_TOP_RIGHT(1, -1, 0, 0, delta);
    PUSH_TOP_RIGHT(-1, 1, 0, 0, delta);
    PUSH_TOP_RIGHT(-1, 1, -1, -delta, delta);
    PUSH_TOP_RIGHT(-1, 0, 1, -delta, delta);
    PUSH_TOP_RIGHT(1, -1, 1, -delta, delta);
    PUSH_TOP_RIGHT(1, 0, -1, -delta, delta);
    PUSH_TOP_RIGHT(0, -1, 1, -delta, 0);
    PUSH_TOP_RIGHT(-1, 0, -1, -delta, delta);
    PUSH_TOP_RIGHT(0, 1, -1, -delta, 0);

    PUSH_BTM_RIGHT(-1, -1, -1, -delta, -delta);
    PUSH_BTM_RIGHT(1, 0, 0, -delta, delta);
    PUSH_BTM_RIGHT(0, 1, 0, -delta, -delta);
    PUSH_BTM_RIGHT(0, 0, 1, delta, -delta);
    PUSH_BTM_RIGHT(-1, -1, 0, -delta, 0);
    PUSH_BTM_RIGHT(1, 1, 0, -delta, 0);
    PUSH_BTM_RIGHT(0, -1, -1, 0, -delta);
    PUSH_BTM_RIGHT(0, 1, 1, 0, -delta);
    
    PUSH_BTM_RIGHT(1, -1, -1, smoothing ? -delta : 0, -delta);
    PUSH_BTM_RIGHT(0, 0, -1, delta, -delta);
    PUSH_BTM_RIGHT(1, 1, 1, -delta, -delta);
    PUSH_BTM_RIGHT(0, -1, 0, -delta, -delta);
    PUSH_BTM_RIGHT(-1, 0, 0, -delta, delta);
    PUSH_BTM_RIGHT(-1, -1, 1, -delta, -delta);
    PUSH_BTM_RIGHT(1, 0, -1, -delta, -delta);
    PUSH_BTM_RIGHT(0, 1, -1, 0, -delta);
    PUSH_BTM_RIGHT(0, -1, 1, 0, -delta);
    PUSH_BTM_RIGHT(-1, 1, 1, -delta, -delta);
    PUSH_BTM_RIGHT(1, 1, -1, -delta, -delta);
    PUSH_BTM_RIGHT(1, -1, 1, -delta, -delta);
    PUSH_BTM_RIGHT(-1, 1, -1, -delta, -delta);
    PUSH_BTM_RIGHT(-1, 0, -1, -delta, -delta);
    PUSH_BTM_RIGHT(-1, 1, 0, -delta, 0);
    PUSH_BTM_RIGHT(1, 0, 1, -delta, -delta);
    PUSH_BTM_RIGHT(1, -1, 0, -delta, 0);
    PUSH_BTM_RIGHT(-1, 0, 1, -delta, -delta);

    PUSH_BTM_LEFT(-1, -1, -1, smoothing ? delta : 0, -delta);
    PUSH_BTM_LEFT(0, -1, -1, delta, 0);
    PUSH_BTM_LEFT(0, 0, 1, delta, delta);
    PUSH_BTM_LEFT(1, 0, 0, -delta, -delta);
    PUSH_BTM_LEFT(0, 1, 0, delta, -delta);
    PUSH_BTM_LEFT(0, 1, 1, delta, 0);
    PUSH_BTM_LEFT(-1, -1, 0, 0, -delta);
    PUSH_BTM_LEFT(1, 1, 0, 0, -delta);

    PUSH_BTM_LEFT(0, -1, 0, delta, -delta);
    PUSH_BTM_LEFT(0, 0, -1, delta, delta);
    PUSH_BTM_LEFT(-1, 0, 0, -delta, -delta);
    PUSH_BTM_LEFT(1, 1, 1, delta, -delta);
    PUSH_BTM_LEFT(1, -1, -1, delta, -delta);
    PUSH_BTM_LEFT(1, -1, 0, 0, -delta);
    PUSH_BTM_LEFT(-1, 1, 0, 0, -delta);
    PUSH_BTM_LEFT(1, 1, -1, delta, -delta);
    PUSH_BTM_LEFT(1, 0, -1, delta, -delta);
    PUSH_BTM_LEFT(-1, 1, -1, delta, -delta);
    PUSH_BTM_LEFT(-1, 1, 1, delta, -delta);
    PUSH_BTM_LEFT(-1, -1, 1, delta, -delta);
    PUSH_BTM_LEFT(-1, 0, 1, delta, -delta);
    PUSH_BTM_LEFT(1, 0, 1, delta, -delta);
    PUSH_BTM_LEFT(0, -1, 1, delta, 0);
    PUSH_BTM_LEFT(0, 1, -1, delta, 0);
    PUSH_BTM_LEFT(1, -1, 1, delta, -delta);
    PUSH_BTM_LEFT(-1, 0, -1, delta, -delta);

    if (jumper)
    {
        PUSH_CORNERS(-1, 0, -1, -1, -1, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT, -1, -1, C_BOTTOMRIGHT, -1, 0, C_BOTTOMLEFT);
        PUSH_CORNER(1, 0, 1, 1, 1, 0, -1, C_TOPRIGHT, -1, 0, C_BOTTOMLEFT);
        PUSH_CORNERS(-1, 1, -1, -1, -1, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT, -1, -1, C_BOTTOMRIGHT, -1, 0, C_BOTTOMLEFT);
        PUSH_CORNERS(-1, -1, -1, -1, -1, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT, -1, -1, C_BOTTOMRIGHT, -1, 0, C_BOTTOMLEFT);
    }
    else
    {
        PUSH_CORNERS2(-1, 0, -1, -1, -1, 0, -1, C_TOPRIGHT, -1, 0, C_BOTTOMLEFT, -1, 0, C_BOTTOMLEFT, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT);
        PUSH_CORNERS(1, 0, 1, 1, 1, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT, -1, -1, C_BOTTOMRIGHT, -1, 0, C_BOTTOMLEFT);
        PUSH_CORNERS2(-1, 1, -1, -1, -1, 0, -1, C_TOPRIGHT, -1, 0, C_BOTTOMLEFT, -1, 0, C_BOTTOMLEFT, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT);
        PUSH_CORNERS2(-1, -1, -1, -1, -1, 0, -1, C_TOPRIGHT, -1, 0, C_BOTTOMLEFT, -1, 0, C_BOTTOMLEFT, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT);
    }

    PUSH_CORNERS(-1, -1, -1, -1, 1, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT, -1, -1, C_BOTTOMRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNERS(-1, 0, 1, -1, 1, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT, -1, -1, C_BOTTOMRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNERS(-1, -1, 1, 1, 1, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT, -1, -1, C_BOTTOMRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNERS(1, 1, 1, -1, 1, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT, -1, -1, C_BOTTOMRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNERS(-1, -1, -1, 1, -1, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT, -1, -1, C_BOTTOMRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNERS(-1, -1, 1, -1, 1, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT, -1, -1, C_BOTTOMRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNERS(1, 1, 1, 1, -1, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT, -1, -1, C_BOTTOMRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNERS(1, 1, -1, -1, -1, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT, -1, -1, C_BOTTOMRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNERS(1, 1, 1, 1, 1, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT, -1, -1, C_BOTTOMRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNERS(1, 1, 1, -1, -1, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT, -1, -1, C_BOTTOMRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNERS(1, -1, -1, 1, -1, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT, -1, -1, C_BOTTOMRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNERS(1, -1, -1, 1, 1, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT, -1, -1, C_BOTTOMRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNERS(-1, -1, -1, 1, 1, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT, -1, -1, C_BOTTOMRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNERS(1, -1, 1, 1, 1, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT, -1, -1, C_BOTTOMRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNERS(-1, 1, 1, -1, 1, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT, -1, -1, C_BOTTOMRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNERS(-1, 1, 1, -1, -1, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT, -1, -1, C_BOTTOMRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNERS(1, 1, -1, 1, -1, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT, -1, -1, C_BOTTOMRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNERS(1, 0, -1, 1, -1, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT, -1, -1, C_BOTTOMRIGHT, -1, 0, C_BOTTOMLEFT);

    PUSH_CORNER(0, 1, 1, -1, 1, -1, -1, C_BOTTOMRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNER(-1, -1, -1, 1, 0, 0, -1, C_TOPRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNER(-1, -1, -1, 0, 1, 0, -1, C_TOPRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNER(1, 1, 1, 1, 0, 0, -1, C_TOPRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNER(1, 1, 0, 1, -1, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT);
    PUSH_CORNER(-1, -1, 1, 0, 1, 0, -1, C_TOPRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNER(1, 1, 0, -1, -1, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT);
    PUSH_CORNER(1, 1, 1, -1, 0, 0, -1, C_TOPRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNER(-1, -1, -1, -1, 0, 0, -1, C_TOPRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNER(0, 1, -1, -1, -1, -1, -1, C_BOTTOMRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNER(0, -1, 1, 1, 1, -1, -1, C_BOTTOMRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNER(1, -1, -1, 1, 0, 0, -1, C_TOPRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNER(0, -1, -1, 1, -1, -1, -1, C_BOTTOMRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNER(0, 1, 1, -1, -1, -1, -1, C_BOTTOMRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNER(1, 1, 1, 0, 1, 0, -1, C_TOPRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNER(-1, 1, 1, -1, 0, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT);
    PUSH_CORNER(1, 1, -1, 0, -1, 0, -1, C_TOPRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNER(-1, 1, 0, -1, -1, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT);
    PUSH_CORNER(-1, -1, -1, 0, -1, -1, -1, C_BOTTOMRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNER(1, -1, 0, 1, 1, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT);
    PUSH_CORNER(0, -1, -1, 1, 1, -1, -1, C_BOTTOMRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNER(1, 1, 1, 0, -1, -1, -1, C_BOTTOMRIGHT, -1, 0, C_BOTTOMLEFT);
    PUSH_CORNER(-1, -1, 0, -1, 1, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT);
    PUSH_CORNER(-1, -1, 0, 1, 1, 0, -1, C_TOPRIGHT, -1, -1, C_BOTTOMRIGHT);
}

#define CORNER_TOPLEFT(dX, dZ)  return Vector3((float)col + dX, height, -((float)row + dZ))
#define CORNER_TOPRIGHT(dX, dZ) return Vector3((float)col + 1.0f + dX, height, -((float)row + dZ));
#define CORNER_BTMRIGHT(dX, dZ) return Vector3((float)col + 1.0f + dX, height, -((float)row +1.0f + dZ));
#define CORNER_BTMLEFT(dX, dZ)  return Vector3((float)col + dX, height, -((float)row + 1.0f + dZ));

#define HEIGHT_LEFT     HeightCell(row, col - 1)
#define HEIGHT_TOPLEFT  HeightCell(row - 1, col - 1)
#define HEIGHT_TOP      HeightCell(row - 1, col)
#define HEIGHT_BTM      HeightCell(row + 1, col)
#define HEIGHT_BTMLEFT  HeightCell(row + 1, col - 1)
#define HEIGHT_TOPRIGHT HeightCell(row - 1, col + 1)
#define HEIGHT_RIGHT    HeightCell(row, col + 1)
#define HEIGHT_BTMRIGHT HeightCell(row + 1, col + 1)

#define H_LEFT_LESS     HEIGHT_LEFT < height
#define H_LEFT_ABOVE    HEIGHT_LEFT > height
#define H_TOP_LESS      HEIGHT_TOP < height
#define H_TOP_EQUALS    HEIGHT_TOP == height
#define H_TOP_ABOVE     HEIGHT_TOP > height
#define H_TOPLEFT_LESS  HEIGHT_TOPLEFT < height
#define H_TOPLEFT_ABOVE HEIGHT_TOPLEFT > height
#define H_TOPLEFT_EQUALS HEIGHT_TOPLEFT == height
#define H_BTM_LESS      HEIGHT_BTM < height
#define H_BTMLEFT_LESS  HEIGHT_BTMLEFT < height
#define H_TOPRIGHT_LESS HEIGHT_TOPRIGHT < height
#define H_RIGHT_LESS    HEIGHT_RIGHT < height
#define H_BTMRIGHT_LESS HEIGHT_BTMRIGHT < height
#define H_RIGHT_EQUALS  HEIGHT_RIGHT == height
#define H_LEFT_EQUALS   HEIGHT_LEFT == height


Vector3 lTerrainSegment::CoordCorner(uint row, uint col, Corner corner)
{
    float height = HeightCell(row, col);

    if(corner == C_TOPLEFT)
    {
        if(row > 0 && col > 0)
        {
            int d0 = Math::Sign(HeightCell(row, col - 1) - height);
            int d1 = Math::Sign(HeightCell(row - 1, col - 1) - height);
            int d2 = Math::Sign(HeightCell(row - 1, col) - height);

            MapPlaneKey key = {d0, d1, d2};

            if(mapTopLeft.Contains(key))
            {
                MapPlaneValue value = mapTopLeft[key];
                CORNER_TOPLEFT(value.dX, value.dZ);
            }
        }
        CORNER_TOPLEFT(0, 0);
    }
    else if(corner == C_TOPRIGHT)
    {
        if(row > 0 && col < widthMap - 1)
        {
            int d0 = Math::Sign(HeightCell(row - 1, col) - height);
            int d1 = Math::Sign(HeightCell(row - 1, col + 1) - height);
            int d2 = Math::Sign(HeightCell(row, col + 1) - height);

            MapPlaneKey key = {d0, d1, d2};

            if(mapTopRight.Contains(key))
            {
                MapPlaneValue value = mapTopRight[key];
                CORNER_TOPRIGHT(value.dX, value.dZ);
            }
        }
        CORNER_TOPRIGHT(0, 0);
    }
    else if(corner == C_BOTTOMRIGHT)
    {
        if(row < heightMap - 1 && col < widthMap - 1)
        {
            int d0 = Math::Sign(HeightCell(row, col + 1) - height);
            int d1 = Math::Sign(HeightCell(row + 1, col + 1) - height);
            int d2 = Math::Sign(HeightCell(row + 1, col) - height);

            MapPlaneKey key = {d0, d1, d2};

            if(mapBtmRight.Contains(key))
            {
                MapPlaneValue value = mapBtmRight[key];
                CORNER_BTMRIGHT(value.dX, value.dZ);
            }
        }
        CORNER_BTMRIGHT(0, 0);
    }
    if((row < heightMap - 1) && col > 0)
    {
        int d0 = Math::Sign(HeightCell(row + 1, col) - height);
        int d1 = Math::Sign(HeightCell(row + 1, col - 1) - height);
        int d2 = Math::Sign(HeightCell(row, col - 1) - height);

        MapPlaneKey key = {d0, d1, d2};
        if(mapBtmLeft.Contains(key))
        {
            MapPlaneValue value = mapBtmLeft[key];
            CORNER_BTMLEFT(value.dX, value.dZ);
        }
    }
    CORNER_BTMLEFT(0, 0);
}


#define CORN(dX, dY, dir) CoordCorner(row + dX, col + dY, dir)

#define ADD_TRIANGLE(dX0, dY0, dir0, dX1, dY1, dir1)    \
    AddTriangle(CORN(0, 0, C_TOPLEFT), CORN(dX0, dY0, dir0), CORN(dX1, dY1, dir1), 1.0f);

#define ADD_TRIANGLE2(dX0, dY0, dir0, dX1, dY1, dir1, dX2, dY2, dir2)   \
    AddTriangle(CORN(dX0, dY0, dir0), CORN(dX1, dY1, dir1), CORN(dX2, dY2, dir2), 1.0f);


void lTerrainSegment::AddTopLeftCornerPlanes(uint row, uint col)
{
    float height = HeightCell(row, col);

    int dLeft = Math::Sign(HEIGHT_LEFT - height);
    int dTopeLeft = Math::Sign(HEIGHT_TOPLEFT - height);
    int dTop = Math::Sign(HEIGHT_TOP - height);
    int dDiagLeft = Math::Sign(HEIGHT_LEFT - HEIGHT_TOPLEFT);
    int dDiagTop = Math::Sign(HEIGHT_TOP - HEIGHT_TOPLEFT);

    MapCornerKey key = {dLeft, dTopeLeft, dTop, dDiagLeft, dDiagTop};

    if(mapCornerTopLeft.Contains(key))
    {
        MapCornerValue value = mapCornerTopLeft[key];
        ADD_TRIANGLE(value.dRow00, value.dCol00, value.corner00, value.dRow01, value.dCol01, value.corner01);
        if (value.dRow10 != value.dRow11 || value.dRow11 != value.dRow12 || value.dCol10 != value.dCol11 || value.dCol11 != value.dCol12 || value.corner10 != value.corner11 || value.corner11 != value.corner12)
        {
            ADD_TRIANGLE2(value.dRow10, value.dCol10, value.corner10, value.dRow11, value.dCol11, value.corner11, value.dRow12, value.dCol12, value.corner12);
        }
        else
        {
            ADD_TRIANGLE(value.dRow10, value.dCol10, value.corner10, value.dRow11, value.dCol11, value.corner11);
        }
    }
}

float lTerrainSegment::GetIntersectionPlane(Ray &ray, lPlane &plane, bool &isClosingTriangleOut)
{
    float distPlane = GetIntersectionPlane(ray, plane);
    lTriangle triangle;
    float distClosing = GetIntersectionClosingTriangle(ray, triangle);

    float distance = Urho3D::M_INFINITY;

    if(distPlane != Urho3D::M_INFINITY && distClosing != Urho3D::M_INFINITY)
    {
        isClosingTriangleOut = distClosing < distPlane;
        distance = distClosing < distPlane ? distClosing : distPlane;
    }
    else if(distPlane != Urho3D::M_INFINITY)
    {
        isClosingTriangleOut = false;
        distance = distPlane;
    }
    else if(distClosing != Urho3D::M_INFINITY)
    {
        isClosingTriangleOut = true;
        distance = distClosing;
    }

    return distance;
}

float lTerrainSegment::GetIntersectionPlane(Ray &ray, lPlane &plane)
{
    float distance = Urho3D::M_INFINITY;

    if(ray.HitDistance(boundingBox) != Urho3D::M_INFINITY)
    {
        uint numPlanes = bufIndPlanes.Size() / 4;

        Vector<float> distances;
        Vector<lPlane> planes;

        for(uint i = 0; i < numPlanes; i++)
        {
            uint index0 = bufIndPlanes[i * 4];
            uint index1 = bufIndPlanes[i * 4 + 1];
            uint index2 = bufIndPlanes[i * 4 + 2];
            uint index3 = bufIndPlanes[i * 4 + 3];

            Vector3 v0 = {bufVert[index0 * 8], bufVert[index0 * 8 + 1], bufVert[index0 * 8 + 2]};
            Vector3 v1 = {bufVert[index1 * 8], bufVert[index1 * 8 + 1], bufVert[index1 * 8 + 2]};
            Vector3 v2 = {bufVert[index2 * 8], bufVert[index2 * 8 + 1], bufVert[index2 * 8 + 2]};
            Vector3 v3 = {bufVert[index3 * 8], bufVert[index3 * 8 + 1], bufVert[index3 * 8 + 2]};

            float dist0 = ray.HitDistance(v0, v1, v2);
            float dist1 = ray.HitDistance(v0, v2, v3);

            if(dist0 != Urho3D::M_INFINITY)
            {
                planes.Push({v0, v1, v2, v3});
                distances.Push(dist0);
            }
            else if(dist1 != Urho3D::M_INFINITY)
            {
                planes.Push({v0, v1, v2, v3});
                distances.Push(dist1);
            }
        }

        if(distances.Size() != 0)
        {
            distance = distances[0];
            plane = planes[0];
            for(uint i = 1; i < distances.Size(); i++)
            {
                if(distances[i] < distance)
                {
                    distance = distances[i];
                    plane = planes[i];
                }
            }
        }
    }

    return distance;
}

float lTerrainSegment::GetIntersectionClosingTriangle(Ray &ray, lTriangle &triangle)
{
    float distance = Urho3D::M_INFINITY;

    if(ray.HitDistance(boundingBox) != Urho3D::M_INFINITY)
    {
        uint numTriangles = bufIndClosingTriangles.Size() / 3;

        Vector<float> distances;
        Vector<lTriangle> triangles;

        for(uint i = 0; i < numTriangles; i++)
        {
            uint index0 = bufIndClosingTriangles[i * 3];
            uint index1 = bufIndClosingTriangles[i * 3 + 1];
            uint index2 = bufIndClosingTriangles[i * 3 + 2];

            Vector3 v0 = {bufVert[index0 * 8], bufVert[index0 * 8 + 1], bufVert[index0 * 8 + 2]};
            Vector3 v1 = {bufVert[index1 * 8], bufVert[index1 * 8 + 1], bufVert[index1 * 8 + 2]};
            Vector3 v2 = {bufVert[index2 * 8], bufVert[index2 * 8 + 1], bufVert[index2 * 8 + 2]};

            float dist = ray.HitDistance(v0, v1, v2);

            if(dist != Urho3D::M_INFINITY)
            {
                triangles.Push({v0, v1, v2});
                distances.Push(dist);
            }
        }

        if(distances.Size() != 0)
        {
            distance = distances[0];
            triangle = triangles[0];
            for(uint i = 1; i < distances.Size(); i++)
            {
                if(distances[i] < distance)
                {
                    distance = distances[i];
                    triangle = triangles[i];
                }
            }
        }
    }

    return distance;
}

void lTerrainSegment::CalculateBoundingBox()
{
    boundingBox.Clear();

    uint numPoints = bufIndPlanes.Size();

    for(uint i = 0; i < numPoints; i++)
    {
        uint index = bufIndPlanes[i];
        float x = bufVert[index * 8];
        float y = bufVert[index * 8 + 1];
        float z = bufVert[index * 8 + 2];
        boundingBox.Merge({x, y, z});
    }
}
