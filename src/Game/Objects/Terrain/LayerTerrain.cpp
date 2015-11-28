#include <stdafx.h>


#include "LayerTerrain.h"


LayerTerrain::LayerTerrain(Context *context) :
    Object(context)
{

}

void LayerTerrain::AddCube(SharedPtr<CubeTerrain> &cube)
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

void LayerTerrain::Build()
{
    PODVector<float> vertexes;
    PODVector<uint> indexes;

    for(auto cube : cubes)
    {
        cube->BuildVertexes(vertexes, indexes);
    }

    SharedPtr<VertexBuffer> vb(new VertexBuffer(gContext));
    SharedPtr<IndexBuffer> ib(new IndexBuffer(gContext));
    SharedPtr<Geometry> geometry(new Geometry(gContext));

    uint numVert = vertexes.Size();
    uint numInd = indexes.Size();

    float *bufVert = new float[numVert];
    uint *bufInd = new uint[numInd];

    for (uint i = 0; i < numVert; i++)
    {
        bufVert[i] = vertexes[i];
    }

    for (uint i = 0; i < numInd; i++)
    {
        bufInd[i] = indexes[i];
    }

    vb->SetShadowed(true);
    vb->SetSize(vertexes.Size() / 8, Urho3D::MASK_POSITION | Urho3D::MASK_NORMAL | Urho3D::MASK_TEXCOORD1);
    vb->SetData(bufVert);

    ib->SetShadowed(true);
    ib->SetSize(numInd, true);
    ib->SetData(bufInd);

    geometry->SetVertexBuffer(0, vb);
    geometry->SetIndexBuffer(ib);
    geometry->SetDrawRange(Urho3D::TRIANGLE_LIST, 0, ib->GetIndexCount());

    model = new Model(gContext);
    Node *node = gScene->CreateChild(NODE_TERRAIN);
    object = node->CreateComponent<StaticModel>();
    object->SetViewMask(VIEW_MASK_FOR_MISSILE);

    Vector<SharedPtr<VertexBuffer>> vbVector;
    Vector<SharedPtr<IndexBuffer>> ibVector;

    model->SetNumGeometries(1);
    model->SetNumGeometryLodLevels(0, 1);
    model->SetGeometry(0, 0, geometry);

    PODVector<uint> morphRange;

    vbVector.Push(vb);
    ibVector.Push(ib);

    model->SetVertexBuffers(vbVector, morphRange, morphRange);
    model->SetIndexBuffers(ibVector);

    model->SetBoundingBox(BoundingBox(-5.0f, 5.0f));

    object->SetModel(model);
    object->SetMaterial(gCache->GetResource<Material>("Materials/TVTerrain.xml"));
    object->SetCastShadows(true);

    SAFE_DELETE(bufVert);
    SAFE_DELETE(bufInd);
}
