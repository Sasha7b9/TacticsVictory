// 2021/02/27 18:48:41 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Core/Math_.h"
#include "Scene/SceneS.h"
#include "Scene/Terrain/LayerTerrain_.h"


Node *LayerTerrain::CreateChild()
{
    return TheScene->CreateChild(NAME_NODE_TERRAIN);
}


void LayerTerrain::Build()
{
    PODVector<float> vertexes;
    PODVector<uint> indexes;

    for (CubeTerrain *cube : cubes)
    {
        cube->BuildVertexes(vertexes, indexes);
    }

    SharedPtr<VertexBuffer> vb(new VertexBuffer(TheContext));
    SharedPtr<IndexBuffer> ib(new IndexBuffer(TheContext));
    SharedPtr<Geometry> geom(new Geometry(TheContext));

    uint numVert = vertexes.Size();
    uint numInd = indexes.Size();

    float *bufVert = new float[(uint64)numVert];
    uint *bufInd = new uint[(uint64)numInd];

    for (uint i = 0; i < numVert; i++)
    {
        bufVert[(uint64)i] = vertexes[i];
    }

    for (uint i = 0; i < numInd; i++)
    {
        bufInd[(uint64)i] = indexes[i];
    }

    vb->SetShadowed(true);
    vb->SetSize(vertexes.Size() / 8, MASK_POSITION | MASK_NORMAL | MASK_TEXCOORD1);
    vb->SetData(bufVert);

    ib->SetShadowed(true);
    ib->SetSize(numInd, true);
    ib->SetData(bufInd);

    geom->SetVertexBuffer(0, vb);
    geom->SetIndexBuffer(ib);
    geom->SetDrawRange(TRIANGLE_LIST, 0, ib->GetIndexCount());

    model = new Model(TheContext);

    Vector<SharedPtr<VertexBuffer>> vbVector;
    Vector<SharedPtr<IndexBuffer>> ibVector;

    model->SetNumGeometries(1);
    model->SetNumGeometryLodLevels(0, 1);
    model->SetGeometry(0, 0, geom);

    PODVector<uint> morphRange;

    vbVector.Push(vb);
    ibVector.Push(ib);

    model->SetVertexBuffers(vbVector, morphRange, morphRange);
    model->SetIndexBuffers(ibVector);

    model->SetBoundingBox(Math::CalculateBoundingBox(bufVert, numVert / 8));

    Node *node = CreateChild();
    node->SetPosition({ -0.5f, 0.0f, -0.5f });
    object = node->CreateComponent<StaticModel>(LOCAL);
    object->SetViewMask(VIEW_MASK_FOR_MISSILE);

    object->SetModel(model);
    object->SetMaterial(TheCache->GetResource<Material>("Materials/TVTerrain.xml"));
    object->SetCastShadows(true);

    delete[] bufVert;
    delete[] bufInd;
}
