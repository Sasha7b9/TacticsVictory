// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include <stdafx.h>
#include "Scene/Objects/GameObject.h"
#include "Scene/Cameras/CameraRTS.h"
#include "Scene/World/Landscape.h"
#include "Scene/World/GameWorld.h"
#include "Scene/Objects/InfoWindow.h"
#include "Scene/Objects/Units/PathFinder/PathUnit.h"


using namespace Pi;


GameObject::GameObject(PiTypeGameObject::S _type) : Node(), typeObject(_type)
{
    AddProperty(new GameObjectProperty(*this));
}


void GameObject::SetMapPosition(float mapX, float mapY)
{
    GetGameObjectProperty().SetMapPosition(mapX, mapY);

    float x = mapX + 0.5f;
    float y = mapY + 0.5f;

    SetNodePosition({x, y, GameWorld::Get()->GetLandscape()->GetHeightAccurately(x, y)});
}


GameObjectController::GameObjectController(PiTypeGameObject::S _typeObject, PiTypeController::S contrType) :
    Controller(contrType),
    typeObject(_typeObject)
{

}

GameObjectController::GameObjectController(const GameObjectController &gameObjectController) :
    Controller(gameObjectController)
{
    typeObject = gameObjectController.typeObject;
}


GameObject &GameObject::GetFromScreen(const Point2D &coord)
{
    GameObjectProperty *property = GameObjectProperty::GetFromScreen(coord);

    return property ? property->gameObject : Empty();
}


GameObject &GameObject::Empty()
{
    static GameObject empty(PiTypeGameObject::Empty);

    return empty;
}


void GameObjectController::Preprocess()
{
    Controller::Preprocess();

    property = (GameObjectProperty *)GetTargetNode()->GetProperty(PiTypeProperty::GameObject);
}


void GameObjectController::Move()
{
    if(property->Selected())
    {
        Point3D coord = GameWorld::Get()->TransformWorldCoordToDisplay(GetTargetNode()->GetWorldPosition());
        coord.x -= property->infoWindow->GetWidgetSize().x / 2;
        coord.y -= property->infoWindow->GetWidgetSize().y / 2;
        coord.x = (float)((int)coord.x);
        coord.y = (float)((int)coord.y);
        property->infoWindow->SetWidgetPosition(coord);
        property->infoWindow->Invalidate();
    }
}


GameObjectProperty::GameObjectProperty(GameObject &_gameObject) :
    Property(PiTypeProperty::GameObject),
    gameObject(_gameObject),
    infoWindow(new InfoWindow())
{}


void GameObjectProperty::SetSelection()
{
    selected = true;
    TheInterfaceMgr->AddWidget(infoWindow);
}


void GameObjectProperty::RemoveSelection()
{
    selected = false;
    TheInterfaceMgr->RemoveWidget(infoWindow);
}


void GameObjectProperty::MouseEvent(uint state)
{
    if(Selectable())
    {
        if (state & (1 << 0))
        {
            Selected() ? RemoveSelection() : SetSelection();
        }

        if(Selected())
        {
            PathUnit::self->SetTarget(Selected() ? gameObject.CastToUnitObject() : nullptr);
        }
//        else
//        {
//            PathUnit::self->Clear();
//        }
    }
}


GameObjectProperty *GameObjectProperty::GetFromScreen(const Point2D &coord)
{
    Ray ray = CameraRTS::self->GetWorldRayFromPoint(coord);

    CollisionData data;

    Point3D p1 = ray.origin;
    Point3D p2 = p1 + ray.direction * ray.tmax;

    if (GameWorld::Get()->DetectCollision(p1, p2, 0.0f, PiKindCollision::RigidBody, &data))
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
