// 2021/12/16 17:21:48 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/World/Water.h"
#include "Scene/World/GameWorld.h"
#include "Scene/World/Landscape.h"


using namespace Pi;


namespace Pi
{
    namespace Water
    {
        struct StructLake
        {
            Integer2D coord;
            Integer2D size;
            bool fog;

            bool Contain(int x, int y)
            {
                if ((x >= coord.x) && (x < coord.x + size.x) && (y >= coord.y) && (y < coord.y + size.y))
                {
                    return true;
                }

                return false;
            }
        };

        Array<StructLake> lakes;

        FogSpaceObject *fog_object = nullptr;

        void CreateLake(const StructLake &lake, bool fog);

        float Level()
        {
            return -0.25;
        }
    }
}


bool Water::UnderWater(int x, int y)
{
    static bool first = true;

    if (first)
    {
        first = false;

        lakes.SetElementCount(3);

        lakes[0] = StructLake{{15, 75}, {10, 10}, false};
        lakes[1] = StructLake{{20, 20}, {12, 25}, false};
        lakes[2] = StructLake{{51, 51}, {45, 45}, true};
    }

    for (int i = 0; i < lakes.GetElementCount(); i++)
    {
        if (lakes[i].Contain(x, y))
        {
            return true;
        }
    }

    return false;
}


void Water::Create()
{
    for (StructLake &lake : lakes)
    {
        CreateLake(lake, lake.fog);
    }

    FogSpace *fog = new FogSpace({(float)GameWorld::Get()->GetLandscape()->GetSizeX_Columns(), (float)GameWorld::Get()->GetLandscape()->GetSizeX_Columns()});
    fog_object = fog->GetObject();
    fog_object->SetFogColor({0.0f, 0.0f, 0.0f});
    fog_object->SetFogDensity(0.05f);
    fog_object->SetFogFunction(PiFogFunction::Linear);
    GameWorld::Get()->GetRootNode()->AppendNewSubnode(fog);
}

void Water::SetFogDensity(float density)
{
    fog_object->SetFogDensity(density);
}

void Water::CreateLake(const StructLake &lake, bool need_fog)
{
    int sizeX = lake.size.x / 4 + 1;
    int sizeY = lake.size.y / 4 + 1;

    WaterBlock *block = new WaterBlock({sizeX, sizeY}, 4, 1.0f, 2.0f, {0, 10.0f});

    ((WaterController *)block->GetController())->Run();
    ((WaterController *)block->GetController())->SetWaterViscosity(4e-3F);
    ((WaterController *)block->GetController())->SetWaterSpeed(4.0e-3F);

    MaterialObject *material = new MaterialObject();

    material->AddAttribute(new DiffuseAttribute({0.0f, 0.0f, 1.0f}));
    material->AddAttribute(new EmissionAttribute({0.0f, 0.0f, 1.0f}));

    for (int x = 0; x < sizeX; x++)
    {
        for (int y = 0; y < sizeY; y++)
        {
            WaterGeometry *geometry = new WaterGeometry(block, {x, y});
            geometry->SetMaterialObject(0, material);
            WaterGeometryObject *object = geometry->GetObject();
            object->SetCollisionExclusionMask(PiKindCollision::Water);
            object->EnableGeometryFlags(PiFlagGeometry::RenderEffectPass);
            object->EnableGeometryEffectFlags(PiFlagGeometryEffect::Opaque | PiFlagGeometryEffect::Accumulate);
            object->Build(geometry);
            block->AppendSubnode(geometry);
        }
    }

    block->SetNodePosition({(float)lake.coord.x - 0.5f, (float)lake.coord.y - 0.5f, Level()});

    GameWorld::Get()->GetRootNode()->AppendNewSubnode(block);

    material->Release();
}


bool Water::DetectHeight(float x, float y, float *height)
{
    CollisionData data;

    //  \todo Не работает. Не детектит воду

    if (GameWorld::Get()->DetectCollision({x - 0.3f, y, 5.0f}, {x - 0.3f, y, -5.0f}, 0.0f, 0, &data))
    {
        *height = data.position.z;
        return true;
    }

    return false;
}
