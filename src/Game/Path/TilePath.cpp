#include <stdafx.h>


#include "TilePath.h"


Vector<SharedPtr<lTilePath>> lTilePath::tiles;
uint lTilePath::numTilesAll = 0;
uint lTilePath::numTilesEnabled = 0;


lTilePath::lTilePath() : Object(gContext)
{
    SharedPtr<VertexBuffer> vb(new VertexBuffer(gContext));
    SharedPtr<IndexBuffer> ib(new IndexBuffer(gContext));
    SharedPtr<Geometry> geometry(new Geometry(gContext));
    SharedPtr<Model> model(new Model(gContext));
    node = gScene->CreateChild("lTilePath");
    SharedPtr<StaticModel> object(node->CreateComponent<StaticModel>());

    const float vertexes[4 * (3 + 2 + 3)] =
    {
        0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
        1.0f, 0.0f, -1.0f,  0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
        0.0f, 0.0f, -1.0f,  0.0f, 1.0f, 0.0f,   0.0f, 1.0f
    };

    const uint16 indexes[6] =
    {
        0, 1, 2,
        0, 2, 3
    };

    vb->SetShadowed(true);
    bool rez = vb->SetSize(4, Urho3D::MASK_POSITION | Urho3D::MASK_NORMAL | Urho3D::MASK_TEXCOORD1);
    rez = vb->SetData(vertexes);

    ib->SetShadowed(true);
    rez = ib->SetSize(6, false);
    rez = ib->SetData(indexes);

    rez = geometry->SetVertexBuffer(0, vb);
    geometry->SetIndexBuffer(ib);
    rez = geometry->SetDrawRange(Urho3D::TRIANGLE_LIST, 0, ib->GetIndexCount());

    Vector<SharedPtr<VertexBuffer>> vbVector;
    Vector<SharedPtr<IndexBuffer>> ibVector;

    vbVector.Push(vb);
    ibVector.Push(ib);

    model->SetNumGeometries(1);
    rez = model->SetNumGeometryLodLevels(0, 1);
    rez = model->SetGeometry(0, 0, geometry);

    PODVector<unsigned> morpRange;
    rez = model->SetVertexBuffers(vbVector, morpRange, morpRange);
    rez = model->SetIndexBuffers(ibVector);

    model->SetBoundingBox(BoundingBox(Vector3(-1.0f, -1.0f, -1.0f), Vector3(1.0f, 1.0f, 1.0f)));

    object->SetModel(model);
    object->SetMaterial(gCache->GetResource<Material>("Materials/TVTerrain.xml"));
    object->SetCastShadows(true);

    // Now draw decal
    SharedPtr<DecalSet> decal(node->CreateComponent<DecalSet>());
    decal->SetMaterial(gCache->GetResource<Material>("Materials/Decals/PathDecal.xml"));
    
    decal->AddDecal(object, {0.5f, 0.05f, -0.5f}, Quaternion(90.0f, 90.0f, 0.0f), 0.8f, 1.0f, 1.0f, Vector2::ZERO, Vector2::ONE);
}

lTilePath::~lTilePath()
{
}

void lTilePath::SetPosition(const Vector3 &pos)
{
    node->SetPosition(pos);
}

void lTilePath::SetVisible(bool visible)
{
    visible ? gScene->NodeAdded(node) : gScene->NodeRemoved(node);
}

void lTilePath::Add(Vector3 &pos)
{
    if(numTilesAll == numTilesEnabled)
    {
        SharedPtr<lTilePath> tile(new lTilePath());
        tile->SetPosition(pos);
        tiles.Push(tile);
        numTilesEnabled++;
        numTilesAll++;
    }
    else if(numTilesEnabled < numTilesAll)
    {
        tiles[numTilesEnabled]->SetVisible(true);
        tiles[numTilesEnabled]->SetPosition(pos);
        numTilesEnabled++;
    }
}

void lTilePath::DisableAll()
{
    for(auto tile : tiles)
    {
        tile->SetVisible(false);
    }
    numTilesEnabled = 0;
}

void lTilePath::RemoveAll()
{
    DisableAll();
    tiles.Resize(0);
}
