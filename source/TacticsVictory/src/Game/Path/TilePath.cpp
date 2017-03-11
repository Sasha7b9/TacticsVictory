// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdafx.h>
#include "TilePath.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Vector<SharedPtr<TilePath>> TilePath::tiles;
uint TilePath::numTilesAll = 0;
uint TilePath::numTilesEnabled = 0;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TilePath::TilePath() : Object(gContext)
{
    float d = 0.0f;

    node = gScene->CreateChild(NODE_TILE_PATH);

    if (tiles.Size() == 0)
    {
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

        SharedPtr<CustomGeometry> geometry(node->CreateComponent<CustomGeometry>());

        geometry->BeginGeometry(0, TRIANGLE_LIST);
        geometry->SetViewMask(VIEW_MASK_FOR_EFFECTS);

        for(int i = 0; i < 6; i++)
        {
            const float *p = vertexes + indexes[i] * 5;
            const float *p0 = p;
            const float *p1 = p + 1;
            const float *p2 = p + 2;
            geometry->DefineVertex(Vector3(*p2, *p1, *p0));
            p0 = p + 3;
            p1 = p + 4;
            geometry->DefineTexCoord(Vector2(*p0, *p1));
            geometry->DefineNormal({0.0f, 1.0f, 0.0f});
        }

        geometry->SetMaterial(gCache->GetResource<Material>("Materials/Decals/PathDecal.xml"));

        geometry->Commit();
    }
    else
    {
        SharedPtr<CustomGeometry> geometry((CustomGeometry*)node->CloneComponent(tiles[0]->node->GetComponent<CustomGeometry>()));
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
TilePath::~TilePath()
{
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TilePath::SetPosition(const Vector3 &pos)
{
    node->SetPosition(pos + Vector3(1.0f, 0.05f, -1.0f));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TilePath::SetVisible(bool visible)
{
    visible ? gScene->NodeAdded(node) : gScene->NodeRemoved(node);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TilePath::Add(Vector3 &pos)
{
    if(numTilesAll == numTilesEnabled)
    {
        SharedPtr<TilePath> tile(new TilePath());
        tile->SetVisible(true);
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

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TilePath::DisableAll()
{
    for(auto tile : tiles)
    {
        tile->SetVisible(false);
    }
    numTilesEnabled = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TilePath::RemoveAll()
{
    DisableAll();
    tiles.Resize(0);
}
