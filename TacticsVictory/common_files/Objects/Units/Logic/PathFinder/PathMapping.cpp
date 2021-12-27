// 2021/12/12 21:37:18 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Logic/PathFinder/PathMapping.h"
#include "Scene/World/GameWorld.h"
#include "Scene/World/Landscape_.h"


using namespace Pi;


PathMapping *PathMapping::empty = nullptr;


void PathMapping::Construct()
{
    static Array<Integer2D> emptyArray;
    emptyArray.SetElementCount(0);

    empty = new PathMapping(*GameObject::empty, emptyArray);
}


void PathMapping::Destruct()
{
    delete empty;
}


PathMapping::PathMapping(const GameObject &object, const Array<Integer2D> &_path) : Node(StringHash(typeid(PathMapping).name()))
{
    SetNodeName(NameForObject(object).c_str());

    path.SetElementCount(_path.GetElementCount());

    for (int i = 0; i < _path.GetElementCount(); i++)
    {
        path[i].x = (float)_path[i].x;
        path[i].y = (float)_path[i].y;

        CellPath *cell = new CellPath(_path[i]);
        AppendNewSubnode(cell);
    }
}


PathMapping *PathMapping::FromScene(const GameObject &object)
{
    return (PathMapping *)GameWorld::self->GetRootNode()->FindFirstNodeByName(NameForObject(object).c_str());
}


String<> PathMapping::NameForObject(const GameObject &object)
{
    return String<>("PathMapping:") + Text::Format("%d", object.id);
}


void PathMapping::Log()
{
    if (path.Empty())
    {
        TheConsoleWindow->AddText("Path is empty");
    }
    else
    {
        TheConsoleWindow->AddText("Path :");
        for (int i = 0; i < path.GetElementCount(); i++)
        {
            TheConsoleWindow->AddFormatText("%f %f", path[i].x, path[i].y);
        }
    }
}


PathMapping::CellPath::CellPath(const Integer2D &position) : Node(StringHash(typeid(PathMapping::CellPath).name()))
{
    SetNodeName("CellPath");
    AppendNewSubnode(CreateMember({(int)((float)position.x + 0.5f), (int)((float)position.y + 0.5f)}));
}


Node *PathMapping::CellPath::CreateMember(const Integer2D &position)
{
    float size = 0.4f;

    PrimitiveGeometry *geometry = new SphereGeometry({size, size, 0.1f});
    PrimitiveGeometryObject *object = geometry->GetObject();
    object->SetCollisionExclusionMask(PiKindCollision::PathUnit);
    object->DisableGeometryFlags(PiFlagGeometry::CastShadows);
    object->SetBuildLevelCount(1);
    geometry->Update();
    object->Build(geometry);
    geometry->Update();

    MaterialObject *material = new MaterialObject();
    DiffuseAttribute *diffuse = new DiffuseAttribute(K::blue);
    material->AddAttribute(diffuse);
    geometry->SetMaterialObject(0, material);
    material->Release();

    MoveTo(position);

    return geometry;
}


void PathMapping::CellPath::MoveTo(const Integer2D &position)
{
    SetNodePosition({(float)position.x + 0.5F, (float)position.y + 0.5F,
        Landscape::self->GetHeightAccurately((float)position.x + 0.5f, (float)position.y + 0.5f)});
}
