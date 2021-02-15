/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include "stdafx.h"
#include "CubeTerrain.h"
#include "LayerTerrain.h"
#include "Core/Math.h"



LayerTerrain::LayerTerrain(Context *context) : Object(context)
{

}


LayerTerrain::~LayerTerrain()
{
}


void LayerTerrain::AddCube(const SharedPtr<CubeTerrain> &cube)
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

    for(CubeTerrain *cube : cubes)
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
    Node *node = TheScene->CreateChild(NODE_TERRAIN);
    object = node->CreateComponent<StaticModel>();
    object->SetViewMask(VIEW_MASK_FOR_MISSILE);

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

    object->SetModel(model);
    object->SetMaterial(TheCache->GetResource<Material>("Materials/TVTerrain.xml"));
    object->SetCastShadows(true);

    SAFE_DELETE_ARRAY(bufVert); //-V809
    SAFE_DELETE_ARRAY(bufInd); //-V809
}


CubeTerrain* LayerTerrain::GetCube(uint row, uint col)
{
    for(auto cube : cubes)
    {
        if(cube->row == row && cube->col == col)
        {
            return cube;
        }
    }

    return nullptr;
}
