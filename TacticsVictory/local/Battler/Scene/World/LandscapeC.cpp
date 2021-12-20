// 2021/12/20 13:59:54 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/World/Landscape_.h"
#include "Graphics/Textures/PoolTextures.h"
#include "Scene/World/GameWorld.h"
#include "Scene/Cameras/CameraRTS.h"
#include "TVBattler.h"


using namespace Pi;


void Landscape::CreateGeometryForZone(TZone *zone)
{
    if (!zone->mutexCreating.TryAcquire())
    {
        return;
    }

    if (zone->state == TZone::State::Empty)
    {
        GeometrySurface *surface = new GeometrySurface();

        for (int i = 0; i < TZone::SIZE_IN_CELLS; i++)
        {
            TCell *cell = zone->GetCell(i);
            if (cell)
            {
                AddFace(surface, cell->coord.x, cell->coord.y);
            }
        }

        surface->texcoordCount = 1;
        surface->surfaceFlags = PiFlagSurface::ValidNormals;

        List<GeometrySurface> *surfaceList = new List<GeometrySurface>();
        surfaceList->Append(surface);
        const List<GeometrySurface> *surfaceTable = surfaceList;

        MaterialObject *material = new MaterialObject();

        Texture *texture = PoolTextures::Get(CanvasTexture::Type::Landscape);

        DiffuseTextureAttribute *diffTexture = new DiffuseTextureAttribute(texture);
        material->AddAttribute(diffTexture);

        Array<MaterialObject *> materialArray;
        materialArray.AddElement(material);

        zone->geometry = new GenericGeometry(1, &surfaceTable, materialArray);

        material->Release();

        delete surfaceList;

        zone->state = TZone::State::Created;
    }

    zone->mutexCreating.Release();
}


Point3D Landscape::GetPointScreen(float x, float y, bool &result)
{
    result = false;

    Ray ray = CameraRTS::self->GetWorldRayFromPoint({x, y});

    CollisionData data;

    Point3D p1 = ray.origin;
    Point3D p2 = p1 + ray.direction * ray.tmax;

    // Сначала определяем столкновение первой попавшейся геометрией
    if (GameWorld::self->DetectCollision(p1, p2, 0.0f, PiKindCollision::PathUnit, &data))
    {
        GeometryObject *object = data.geometry->GetObject();

        if (object->GetCollisionExclusionMask() == PiKindCollision::Landscape)
        {
            result = true;
            return data.position;
        }
    }

    return Point3D::ZERO;
}


void Landscape::ReloadIfNeed()
{
    static machine prevDateTime = -1;

    Landscape::self->file.Open();

    machine dateTime = Landscape::self->file.GetDateTimeCreate();

    Landscape::self->file.Close();

    if (prevDateTime != -1)
    {
        if (prevDateTime != dateTime)
        {
            Battler::self->ReloadLandscape();
        }
    }

    prevDateTime = dateTime;

    Landscape::self->file.Close();
}
