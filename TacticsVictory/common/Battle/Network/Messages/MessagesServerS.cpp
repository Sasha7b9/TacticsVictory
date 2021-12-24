// 2021/12/21 21:56:47 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Messages/MessagesServer_.h"
#include "Objects/GameObject_.h"
#include "Objects/Units/Unit_.h"
#include "Objects/Units/Air/AirUnit_.h"
#include "Objects/Units/Ground/GroundUnit_.h"
#include "Objects/Units/Water/WaterUnit_.h"


using namespace Pi;


bool MessageCreateLandscape::HandleMessage(Player *) const
{
    return true;
}


bool MessageCreateGameObject::HandleMessage(Player *) const
{
    return false;
}


bool MessageGameObjectNodeTransform::HandleMessage(Player *sender) const
{
    return true;
}


MessageCreateLandscape::MessageCreateLandscape(pchar _name_file) : Message(PiTypeMessage::CreateLandscape)
{
    pchar pointer = &_name_file[strlen(_name_file) - 1];

    while (*pointer != '\\' && *pointer != '/')
    {
        pointer--;
    }

    pointer--;

    while (*pointer != '\\' && *pointer != '/')
    {
        pointer--;
    }

    name_file = pointer + 1;
}


void MessageCreateGameObject::AppendObject(GameObject *object)
{
    if (num_objects == MAX_NUM_OBJECTS)
    {
        LOG_ERROR_TRACE("buffer overflow");
        return;
    }

    id[num_objects] = object->GetID();
    transform[num_objects] = object->GetNodeTransform();
    type[num_objects][0] = (int)object->typeGameObject;

    FillUnit(object->GetUnitObject());

    num_objects++;
}


void MessageCreateGameObject::FillUnit(UnitObject *unit)
{
    type[num_objects][1] = (int)unit->typeUnit;

    if (type[num_objects][1] == (int)TypeUnit::Air)
    {
        type[num_objects][2] = (int)unit->GetAirUnit()->typeAirUnit;
    }
    else if (type[num_objects][1] == (int)TypeUnit::Ground)
    {
        type[num_objects][2] = (int)unit->GetGroundUnit()->typeGroundUnit;
    }
    else if (type[num_objects][1] == (int)TypeUnit::Water)
    {
        type[num_objects][2] = (int)unit->GetWaterUnit()->typeWaterUnit;
    }
}


void MessageGameObjectNodeTransform::AddObject(GameObject *object)
{
    id[num_objects] = object->GetID();

    position[num_objects] = object->GetNodePosition();

    num_objects++;
}
