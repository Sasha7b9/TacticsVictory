// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/GameObject_.h"
#include "Scene/World/Landscape_.h"
#include "Scene/World/GameWorld.h"
#include "Objects/Units/Logic/PathFinder/PathFinder.h"
#include "Objects/Units/Logic/PathFinder/PathMapping.h"
#include "Objects/Units/Unit_.h"
#include "Objects/Ammo/Ammo_.h"
#include "PeriodicTasks.h"
#include "GameState.h"
#include "Objects/PoolObjects_.h"


using namespace Pi;


GameObject     *GameObject::empty = nullptr;
int             GameObject::createdObjects = 0;
Map<GameObject> GameObject::objects;


void GameObject::Construct()
{
    PoolObjects::Consruct();

#ifdef PiCLIENT

    empty = new GameObject(TypeGameObject::Empty, 0, new GameObjectController(nullptr));

    AmmoObject::Construct();
    UnitObject::Construct();

#endif
}


void GameObject::Destruct()
{
#ifdef PiCLIENT

    AmmoObject::Destruct();
    UnitObject::Destruct();

    Property *property = empty->GetProperty(PiTypeProperty::GameObject);

    delete property;

    delete empty;

#endif

    PoolObjects::Destruct();
}


GameObject::GameObject(TypeGameObject type, int _id, GameObjectController *_controller) :
    Node(),
    typeGameObject(type),
    controller(_controller),
    id(_id == -1 ? ++createdObjects : _id),
    numberThread(id % TaskMain::NumberThreads())
{
    SetController(controller);

    AddProperty(new GameObjectProperty(*this));

    nodeGeometry = new Node();

    nodeGeometry->SetNodeName("Geometry");

    AppendNewSubnode(nodeGeometry);

    objects.Insert(this);
}


GameObject::~GameObject()
{
    delete controller;
}


bool GameObject::AppendInGame(int _x, int _y)
{
    if (!GameState::landscapeCreated)
    {
        return false;
    }

    float x = (float)_x;
    float y = (float)_y;

    bool append = false;

    if (IsUnit())
    {
        UnitObject *unit = GetUnitObject();

        if (unit->typeUnit == TypeUnit::Air) //-V522
        {
            float height = 5.0f;

            if (Landscape::self->AboveSurface(_x, _y) && !Landscape::self->UnderWater(_x, _y))
            {
                height += Landscape::self->GetHeightAccurately(x, y);
            }
            unit->GetUnitController()->param->position = Point3D(x, y, height);
            append = true;
        }
        else if (unit->typeUnit == TypeUnit::Ground)
        {
            if (!Landscape::self->UnderWater(_x, _y))
            {
                float height = Landscape::self->GetHeightAccurately(x, y);
                unit->GetUnitController()->param->position = Point3D(x, y, height);
                append = true;
            }
        }
        else if (unit->typeUnit == TypeUnit::Water)
        {
            if (Landscape::self->UnderWater(_x, _y))
            {
                unit->GetUnitController()->param->position = Point3D(x, y, Water::Level());
                append = true;
            }
        }
    }

    if (append)
    {
        GameWorld::self->GetRootNode()->AppendNewSubnode(this);
        return true;
    }

    return false;
}


void GameObject::SetNodePosition(const Point3D &position)
{
    Node::SetNodePosition(position);
}


GameObjectController::GameObjectController(GameObject *_object) : gameObject(_object)
{

}


GameObject &GameObject::GetFromScreen(const Point2D &coord)
{
    GameObjectProperty *property = GameObjectProperty::GetFromScreen(coord);

    return property ? property->gameObject : *empty;
}


void GameObject::SetDirection(const Vector3D &direction, const Vector3D &up)
{
    Vector3D front = direction;
    Vector3D right = Cross(front, up).Normalize();
    Vector3D top = Cross(right, front).Normalize();

    GetNodeGeometry()->SetNodeMatrix3D({right, front, top});
}


Node *GameObject::CreateNodeForGeometry(pchar name, Node *_nodeGeometry)
{
    Node *node = new Node();
    node->SetNodeName(name);
    node->AppendNewSubnode(_nodeGeometry);
    return node;
}


void GameObjectController::Preprocess()
{
    property = (GameObjectProperty *)gameObject->GetProperty(PiTypeProperty::GameObject);
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
