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


MessageCreateGameObject::MessageCreateGameObject(GameObject *object) :
    Message(PiTypeMessage::CreateGameObject),
    id(object->GetID()),
    typeGameObject(object->typeGameObject),
    transform(object->GetNodeTransform())
{
    if (typeGameObject == TypeGameObject::Unit)
    {
        FillUnit(object->GetUnitObject());
    }
}


void MessageCreateGameObject::FillUnit(UnitObject *unit)
{
    typeUnit = unit->typeUnit;

    if (typeUnit == TypeUnit::Air)
    {
        FillAirUnit(unit->GetAirUnit());
    }
    else if (typeUnit == TypeUnit::Ground)
    {
        FillGroundUnit(unit->GetGroundUnit());
    }
    else if (typeUnit == TypeUnit::Water)
    {
        FillWaterUnit(unit->GetWaterUnit());
    }
}


void MessageCreateGameObject::FillAirUnit(AirUnitObject *unit)
{
    typeAirUnit = unit->typeAirUnit;
}


void MessageCreateGameObject::FillGroundUnit(GroundUnitObject *unit)
{
    typeGroundUnit = unit->typeGroundUnit;
}


void MessageCreateGameObject::FillWaterUnit(WaterUnitObject *unit)
{
    typeWaterUnit = unit->typeWaterUnit;
}


MessageGameObjectNodeTransform::MessageGameObjectNodeTransform(GameObject *object) :
    Message(PiTypeMessage::SendGameObjectNodeTransform),
    id(object->GetID()),
    transform(object->GetNodeTransform())
{
}
