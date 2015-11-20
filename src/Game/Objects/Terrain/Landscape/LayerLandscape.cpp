#include <stdafx.h>


#include "LayerLandscape.h"


LayerLandscape::LayerLandscape(Context *context) :
    Object(context)
{

}

void LayerLandscape::AddCube(SharedPtr<CubeLandscape> &cube)
{
    cubes.Push(cube);
}

void LayerLandscape::Create()
{
    for(auto cube : cubes)
    {
        cube->Create();
    }
}

void LayerLandscape::Build()
{
    for(auto cube : cubes)
    {
        cube->BuildVertexes();
    }

    model = new Model(gContext);
    Node *node = gScene->CreateChild(NODE_TERRAIN);
    object = node->CreateComponent<StaticModel>();
    object->SetViewMask(VIEW_MASK_FOR_MISSILE);

    Vector<SharedPtr<VertexBuffer>> vbVector;
    Vector<SharedPtr<IndexBuffer>> ibVector;

    model->SetNumGeometries(cubes.Size());
    model->SetNumGeometryLodLevels(0, 1);

    for (uint i = 0; i < cubes.Size(); i++)
    {
        model->SetGeometry(i, 0, cubes[i]->geometry);
        vbVector.Push(cubes[i]->vb);
        ibVector.Push(cubes[i]->ib);
    }

    PODVector<uint> morphRange;

    model->SetVertexBuffers(vbVector, morphRange, morphRange);
    model->SetIndexBuffers(ibVector);

    model->SetBoundingBox(BoundingBox(-500.0f, 500.0f));

    object->SetModel(model);
    object->SetMaterial(gCache->GetResource<Material>("Materials/TVTerrain.xml"));
    object->SetCastShadows(true);

    node->SetPosition({-250.0f, 0.0f, 0.0f});
}
