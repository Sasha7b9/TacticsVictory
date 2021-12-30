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
#include "Objects/Units/Water/WaterUnit_.h"
#include "Objects/Units/Air/AirUnit_.h"
#include "Objects/Staff/Commander_.h"

#ifdef PiCLIENT
    #include "Objects/InfoWindow.h"
#endif


using namespace Pi;


GameObject     *GameObject::empty = nullptr;
int             GameObject::createdObjects = 0;
Map<GameObject> GameObject::objects;


static const GameObjectParameters parametersEmpty
{
    {},
    true,
    0
};


void GameObject::Construct()
{
    PoolObjects::Consruct();

#ifdef PiCLIENT

    empty = new GameObject(TypeGameObject::Empty, &parametersEmpty, 0);

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


GameObject::GameObject(TypeGameObject type, const GameObjectParameters *_param, int _id) :
    Node(),
    typeGameObject(type)
{
    int id = _id == -1 ? ++createdObjects : _id;

    params = PoolObjects::AllocateParameters(id);

    *params = *_param;

    params->isDead = false;
    params->id = id;
    params->numberThread = params->id %TaskMain::NumberThreads();

    AddProperty(new GameObjectProperty(*this));

    nodeGeometry = new Node();

    nodeGeometry->SetNodeName("Geometry");

    AppendNewSubnode(nodeGeometry);

    objects.Insert(this);
}


GameObject::~GameObject()
{
    delete commander;
    delete driver;
}


void GameObject::AppendTask(CommanderTask *task)
{
    task->SetGameObject(this);
    commander->AppendTask(task);
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
            unit->params->position = Point3D(x, y, height);
            append = true;
        }
        else if (unit->typeUnit == TypeUnit::Ground)
        {
            if (!Landscape::self->UnderWater(_x, _y))
            {
                float height = Landscape::self->GetHeightAccurately(x, y);
                unit->params->position = Point3D(x, y, height);
                append = true;
            }
        }
        else if (unit->typeUnit == TypeUnit::Water)
        {
            if (Landscape::self->UnderWater(_x, _y))
            {
                unit->params->position = Point3D(x, y, Water::Level());
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


void GameObject::Move(float dT)
{
#ifdef PiCLIENT

    if (property->Selected())
    {
        Point3D coord = GameWorld::self->TransformWorldCoordToDisplay(GetWorldPosition());
        coord.x -= property->infoWindow->GetWidgetSize().x / 2;
        coord.y -= property->infoWindow->GetWidgetSize().y / 2;
        coord.x = (float)((int)coord.x);
        coord.y = (float)((int)coord.y);
        property->infoWindow->SetWidgetPosition(coord);
        property->infoWindow->Invalidate();
    }

#endif
}


void GameObject::Preprocess()
{
    property = (GameObjectProperty *)GetProperty(PiTypeProperty::GameObject);
}


bool GameObject::CanExecute(CommanderTask::Type task) const
{
    switch (task)
    {
    case CommanderTask::Type::Move:
    case CommanderTask::Type::Rotate:
    case CommanderTask::Type::Test:
        return true;
        break;

    case CommanderTask::Type::Dive:
    {
        UnitObject *unit = GetUnitObject();
        if (unit)
        {
            WaterUnitObject *water = unit->GetWaterUnit();
            if (water)
            {
                if (water->typeWaterUnit == TypeWaterUnit::Submarine)
                {
                    return true;
                }
            }
        }
    }
    break;

    case CommanderTask::Type::FreeFlight:
    {
        UnitObject *unit = GetUnitObject();
        if (unit)
        {
            AirUnitObject *air = unit->GetAirUnit();
            if (air->typeAirUnit == TypeAirUnit::Airplane)
            {
                return true;
            }
        }
    }
    break;

    case CommanderTask::Type::Count:
        break;
    }

    return false;
}


GameObject &GameObject::GetFromScreen(const Point2D &coord)
{
    GameObjectProperty *property = GameObjectProperty::GetFromScreen(coord);

    return property ? property->gameObject : *empty;
}


void GameObject::SetDirection(const Vector3D &direction, const Vector3D &up)
{
    Vector3D right = Cross(direction, up).Normalize();

    GetNodeGeometry()->SetNodeMatrix3D({right, direction, up});
}


Node *GameObject::CreateNodeForGeometry(pchar name, Node *_nodeGeometry)
{
    Node *node = new Node();
    node->SetNodeName(name);
    node->AppendNewSubnode(_nodeGeometry);
    return node;
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
