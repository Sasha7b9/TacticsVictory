// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include <stdafx.h>
#include "Scene/Objects/GameObject.h"
#include "Scene/Cameras/CameraRTS.h"
#include "Scene/World/Landscape.h"
#include "Scene/World/GameWorld.h"


using namespace Pi;


GameObject::GameObject() : Node()
{
    AddProperty(new GameObjectProperty(this));
}


void GameObject::SetMapPosition(float mapX, float mapY)
{
    GetGameObjectProperty()->SetMapPosition(mapX, mapY);

    float x = mapX + 0.5f;
    float y = mapY + 0.5f;

    SetNodePosition({x, y, GameWorld::Get()->GetLandscape()->GetHeight(x, y)});
}


void GameObject::SetNodePosition(const Point3D &position)
{
    Node::SetNodePosition(position);
}


GameObjectProperty *GameObject::GetGameObjectProperty()
{
    return (GameObjectProperty *)GetProperty(PiTypeProperty::GameObject);
}


GameObjectController::GameObjectController(Type _gameObjectType, PiTypeController::S contrType) :
    Controller(contrType),
    gameObjectType(_gameObjectType)
{

}

GameObjectController::GameObjectController(const GameObjectController &gameObjectController) :
    Controller(gameObjectController)
{
    gameObjectType = gameObjectController.gameObjectType;
}

GameObjectController::~GameObjectController()
{

}

void GameObjectController::Preprocess()
{
    Controller::Preprocess();
}


GameObject &GameObject::Empty()
{
    static GameObject empty;
    return empty;
}


void GameObjectController::Move()
{
    Controller::Move();

    GameObjectProperty *property = (GameObjectProperty *)GetTargetNode()->GetProperty(PiTypeProperty::GameObject);

    if(property->IsSelected())
    {
        Point3D coord = GameWorld::Get()->TransformWorldCoordToDisplay(GetTargetNode()->GetWorldPosition());
        coord.x -= property->indicator->GetWidgetSize().x / 2;
        coord.y -= property->indicator->GetWidgetSize().y / 2;
        coord.x = (float)((int)coord.x);
        coord.y = (float)((int)coord.y);
        property->indicator->SetWidgetPosition(coord);
        property->indicator->Invalidate();
    }
}
