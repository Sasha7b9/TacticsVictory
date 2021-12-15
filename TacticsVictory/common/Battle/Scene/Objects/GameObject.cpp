// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include <stdafx.h>
#include "Scene/Objects/GameObject.h"
#include "Scene/Cameras/CameraRTS.h"
#include "Scene/World/Landscape.h"
#include "Scene/World/GameWorld.h"
#include "Scene/Objects/InfoWindow.h"
#include "Scene/Objects/Units/PathFinder/PathFinder.h"
#include "Scene/Objects/Units/PathFinder/PathMapping.h"
#include "Scene/Objects/Units/Unit.h"


using namespace Pi;


GameObject *GameObject::empty = nullptr;
int         GameObject::createdObjects = 0;


void GameObject::Construct()
{
    empty = new GameObject(PiTypeGameObject::Empty);

    UnitObject::Construct();
}


void GameObject::Destruct()
{
    UnitObject::Destruct();

    Property *property = empty->GetProperty(PiTypeProperty::GameObject);

    delete property;

    delete empty;
}


GameObject::GameObject(PiTypeGameObject::S _type) : Node(), typeObject(_type)
{
    id = ++createdObjects;

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

    return property ? property->gameObject : *empty;
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
    finder->Find([this](const Array<Point2DI> &_path)
        {
            GameWorld::Get()->GetRootNode()->AppendNewSubnode(new PathMapping(gameObject, _path));
        }
    );
}


void GameObjectProperty::RemoveSelection()
{
    selected = false;
    TheInterfaceMgr->RemoveWidget(infoWindow);

    delete PathMapping::FromScene(gameObject);
}


void GameObjectProperty::MouseEvent(uint state)
{
    if(Selectable())
    {
        if (state & (1 << 0))
        {
            Selected() ? RemoveSelection() : SetSelection();
        }
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
