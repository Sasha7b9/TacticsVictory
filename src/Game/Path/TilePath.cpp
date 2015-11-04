#include <stdafx.h>


#include "TilePath.h"


Vector<SharedPtr<TilePath>> TilePath::tiles;
uint TilePath::numTilesAll = 0;
uint TilePath::numTilesEnabled = 0;


TilePath::TilePath() : Object(gContext)
{
    const float vertexes[4 * (3 + 2)] =
    {
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        0.0f, 0.0f, -1.0f, 0.0f, 1.0f
    };

    const uint16 indexes[6] =
    {
        2, 1, 0,
        3, 2, 0
    };

    node = gScene->CreateChild("TilePath");

    SharedPtr<UCustomGeometry> geometry(node->CreateComponent<UCustomGeometry>());

    geometry->BeginGeometry(0, Urho3D::TRIANGLE_LIST);

    for(int i = 0; i < 6; i++)
    {
        const float *p = vertexes + indexes[i] * 5;
        geometry->DefineVertex(Vector3(*p++, *p++, *p++));
        geometry->DefineTexCoord(Vector2(*p++, *p));
    }

    geometry->Commit();

    geometry->SetMaterial(gCache->GetResource<Material>("Materials/Decals/PathDecal.xml"));

    Material* material = geometry->GetMaterial(0);

    geometry->Commit();
}

TilePath::~TilePath()
{
}

void TilePath::SetPosition(const Vector3 &pos)
{
    node->SetPosition(pos + Vector3(0.0f, 0.05f, 0.0f));
}

void TilePath::SetVisible(bool visible)
{
    visible ? gScene->NodeAdded(node) : gScene->NodeRemoved(node);
}

void TilePath::Add(Vector3 &pos)
{
    if(numTilesAll == numTilesEnabled)
    {
        for (int i = 0; i < 50; i++)
        {
            SharedPtr<TilePath> tile(new TilePath());
            tile->SetVisible(false);
            tiles.Push(tile);
        }

        numTilesAll += 50;

        tiles[numTilesEnabled]->SetVisible(true);
        tiles[numTilesEnabled]->SetPosition(pos);
        numTilesEnabled++;
    }
    else if(numTilesEnabled < numTilesAll)
    {
        tiles[numTilesEnabled]->SetVisible(true);
        tiles[numTilesEnabled]->SetPosition(pos);
        numTilesEnabled++;
    }
}

void TilePath::DisableAll()
{
    for(auto tile : tiles)
    {
        tile->SetVisible(false);
    }
    numTilesEnabled = 0;
}

void TilePath::RemoveAll()
{
    DisableAll();
    tiles.Resize(0);
}
