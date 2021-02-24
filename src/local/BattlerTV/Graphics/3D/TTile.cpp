// 2021/02/24 16:50:10 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Graphics/3D/TTile.h"
#include "Scene/TCScene.h"


Tile::Tile(Context *context) : LogicComponent(context)
{

}


Tile::~Tile()
{

}


void Tile::RegisterObject()
{
    TheContext->RegisterFactory<Tile>();
}


void Tile::OnNodeSet(Node *node)
{
    if (node)
    {
        node_ = node->CreateChild();
    }

    LogicComponent::OnNodeSet(node ? node_ : node);
}


void Tile::Start()
{
    float d = 0.0f;

    node_->SetScale(100);

    const float vertexes[4 * (3 + 2)] =
    {
        0.0f + d, 0.0f, 0.0f + d, 0.0f, 1.0f,
        1.0f - d, 0.0f, 0.0f + d, 1.0f, 1.0f,
        1.0f - d, 0.0f, -1.0f + d, 1.0f, 0.0f,
        0.0f + d, 0.0f, -1.0f + d, 0.0f, 0.0f
    };

    const uint16 indexes[6] =
    {
        2, 1, 0,
        3, 2, 0
    };

    SharedPtr<CustomGeometry> geometry(node_->CreateComponent<CustomGeometry>());

    geometry->BeginGeometry(0, TRIANGLE_LIST);
    geometry->SetViewMask(VIEW_MASK_FOR_EFFECTS);

    for (int i = 0; i < 6; i++)
    {
        const float *p = vertexes + indexes[i] * 5;
        const float *p0 = p;
        const float *p1 = p + 1;
        const float *p2 = p + 2;
        geometry->DefineVertex(Vector3(*p2, *p1, *p0));
        p0 = p + 3;
        p1 = p + 4;
        geometry->DefineTexCoord(Vector2(*p0, *p1));
        geometry->DefineNormal({ 0.0f, 1.0f, 0.0f });
    }

    geometry->SetMaterial(TheCache->GetResource<Material>("Materials/Decals/Tile.xml"));

    geometry->Commit();

    Disable();
}


void Tile::Enable()
{
    node_->SetEnabled(true);
}


void Tile::Disable()
{
    node_->SetEnabled(false);
}


bool Tile::IsEnabled() const
{
    return node_->IsEnabled();
}
