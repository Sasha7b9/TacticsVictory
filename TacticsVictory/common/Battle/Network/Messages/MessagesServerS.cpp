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


bool MessageGameObjectState::HandleMessage(Player *sender) const
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

    StateObject &state = states[num_objects];

    state.id = object->id;

    UnitObject *unit = object->GetUnitObject();
    UnitParameters &param = *unit->GetUnitController()->param;

    state.position = param.position;
    state.direction = param.direction;
    state.up = param.up;
    state.type[0] = (int)object->typeGameObject;

    FillUnit(object->GetUnitObject());

    num_objects++;
}


void MessageCreateGameObject::FillUnit(UnitObject *unit)
{
    StateObject &state = states[num_objects];

    state.type[1] = (int)unit->typeUnit;

    if (state.type[1] == (int)TypeUnit::Air)
    {
        state.type[2] = (int)unit->GetAirUnit()->typeAirUnit; //-V522
    }
    else if (state.type[1] == (int)TypeUnit::Ground)
    {
        state.type[2] = (int)unit->GetGroundUnit()->typeGroundUnit; //-V522
    }
    else if (state.type[1] == (int)TypeUnit::Water)
    {
        state.type[2] = (int)unit->GetWaterUnit()->typeWaterUnit; //-V522
    }
}


void MessageGameObjectState::AddObject(GameObject *object)
{
    StateObject &state = states[num_objects];

    state.id = object->id;

    UnitParameters &param = *object->GetUnitObject()->GetUnitController()->param; //-V522

    state.position = param.position;
    state.direction = param.direction;
    state.up = param.up;

    num_objects++;
}
