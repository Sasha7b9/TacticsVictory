#include <stdafx.h>


tvPlane::tvPlane(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3 &p3) :
    Object(gContext)
{
    Create(p0, p1, p2, p3);
}

void tvPlane::Create(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3 &p3)
{
    float vertexes[] =
    {
        p0.x_, p0.y_, p0.z_, 0.0f, 0.0f,
        p1.x_, p1.y_, p1.z_, 1.0f, 0.0f,
        p2.x_, p2.y_, p2.z_, 1.0f, 1.0f,
        p3.x_, p3.y_, p3.z_, 0.0f, 1.0f
    };

    ushort indexes[] =
    {
        0, 1, 2, 2, 3, 0,
        0, 2, 1, 2, 0, 3
    };

    SharedPtr<VertexBuffer> vb(new VertexBuffer(gContext));
    vb->SetShadowed(true);
    vb->SetSize(4, Urho3D::MASK_POSITION | Urho3D::MASK_TEXCOORD1);
    vb->SetData(vertexes);

    SharedPtr<IndexBuffer> ib(new IndexBuffer(gContext));
    ib->SetShadowed(true);
    ib->SetSize(12, false);
    ib->SetData(indexes);

    Geometry *geometry = new Geometry(gContext);
    geometry->SetVertexBuffer(0, vb);
    geometry->SetIndexBuffer(ib);
    geometry->SetDrawRange(Urho3D::TRIANGLE_LIST, 0, ib->GetIndexCount());

    SharedPtr<Model> model(new Model(gContext));
    Vector<SharedPtr<VertexBuffer> > vbVector;
    Vector<SharedPtr<IndexBuffer> > ibVector;
    vbVector.Push(vb);
    ibVector.Push(ib);
    model->SetNumGeometries(1);
    model->SetNumGeometryLodLevels(0, 1);
    model->SetGeometry(0, 0, geometry);

    PODVector<unsigned> morpRange;
    model->SetVertexBuffers(vbVector, morpRange, morpRange);
    model->SetIndexBuffers(ibVector);
    model->SetBoundingBox(BoundingBox(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)));

    Node *node = gScene->CreateChild("node");
    StaticModel *object = node->CreateComponent<StaticModel>();
    object->SetModel(model);
    object->SetMaterial(gCache->GetResource<Material>("Materials/TVTerrain.xml"));
}