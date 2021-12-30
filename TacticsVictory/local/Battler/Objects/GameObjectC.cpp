// 2021/12/20 13:36:32 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/GameObject_.h"
#include "Objects/InfoWindow.h"
#include "Scene/World/GameWorld.h"
#include "Objects/Units/Logic/PathFinder/PathFinder.h"
#include "Objects/Units/Logic/PathFinder/PathMapping.h"
#include "Scene/Cameras/CameraRTS.h"


using namespace Pi;


GameObjectProperty::GameObjectProperty(GameObject &_gameObject) :
    Property(PiTypeProperty::GameObject),
    gameObject(_gameObject),
    infoWindow(new InfoWindow())
{
}


GameObjectProperty::~GameObjectProperty()
{
    delete infoWindow;
}


void GameObjectProperty::SetSelection()
{
    selected = true;
    TheInterfaceMgr->AddWidget(infoWindow);

    PathFinder *finder = new PathFinder(gameObject.GetWorldPosition().GetPoint2D(), {50.0f, 50.0f});
    gameObject.AppendNewSubnode(finder);
    finder->Find([this](const Array<Integer2D> &_path)
            {
                GameWorld::self->GetRootNode()->AppendNewSubnode(new PathMapping(gameObject, _path));
            });
}


void GameObjectProperty::RemoveSelection()
{
    selected = false;
    TheInterfaceMgr->RemoveWidget(infoWindow);

    delete PathMapping::FromScene(gameObject);
}


GameObjectProperty *GameObjectProperty::GetFromScreen(const Point2D &coord)
{
    Ray ray = CameraRTS::self->GetWorldRayFromPoint(coord);

    CollisionData data;

    Point3D p1 = ray.origin;
    Point3D p2 = p1 + ray.direction * ray.tmax;

    if (GameWorld::self->DetectCollision(p1, p2, 0.0f, PiKindCollision::RigidBody, &data))
    {
        Node *node = data.geometry->GetSuperNode();

        while (node)
        {
            GameObjectProperty *property = (GameObjectProperty *)node->GetProperty(PiTypeProperty::GameObject);

            if (property)
            {
                return property;
            }

            node = node->GetSuperNode();
        }
    }

    return nullptr;
}

