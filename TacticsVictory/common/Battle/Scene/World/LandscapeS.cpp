// 2021/12/20 14:15:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/World/Landscape_.h"


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

        DiffuseAttribute *diffuse = new DiffuseAttribute(K::black);
        material->AddAttribute(diffuse);

        Array<MaterialObject *> materialArray;
        materialArray.AddElement(material);

        zone->geometry = new GenericGeometry(1, &surfaceTable, materialArray);

        material->Release();

        delete surfaceList;

        zone->state = TZone::State::Created;
    }

    zone->mutexCreating.Release();
}


void Landscape::ReloadIfNeed()
{

}
