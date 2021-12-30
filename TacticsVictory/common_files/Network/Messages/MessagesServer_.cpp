// 2021/12/21 17:52:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Messages/MessagesServer_.h"
#include "Objects/GameObject_.h"
#include "Objects/Units/Unit_.h"
#include "Objects/Units/Air/AirUnit_.h"
#include "Objects/Units/Ground/GroundUnit_.h"
#include "Objects/Units/Water/WaterUnit_.h"

#ifdef PiCLIENT
    #include "Scene/World/Landscape_.h"
    #include "Scene/World/GameWorld.h"
    #include "TVBattler.h"
    #include "Objects/Units/Air/Airplane_.h"
    #include "Objects/Units/Ground/Tank_.h"
    #include "Objects/Units/Water/Submarine_.h"
    #include "GameState.h"
    #include "Graphics/Effects/SmokeTrail.h"
    #include "Network/Messages/MessagesClient_.h"
#endif


using namespace Pi;


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


void MessageCreateLandscape::Compress(Compressor &data) const
{
    data << name_file.Length() + 1;
    data << name_file.c_str();
}


bool MessageCreateLandscape::Decompress(Decompressor &data)
{
    int size = 0;
    data >> size;
    name_file.SetLength(size);

    data.Read((char *)name_file.c_str(), (uint)size);

    return true;
}


bool MessageCreateLandscape::HandleMessage(Player *sender) const
{
#ifdef PiCLIENT

    LOG_WRITE("Load landscape %s", name_file.c_str());
    new Landscape((Battler::self->DataPath() + name_file.c_str()).c_str());
    GameWorld::self->GetRootNode()->AppendNewSubnode(Landscape::self);
    Water::Create();

#endif

    return true;
}


void MessageCreateGameObject::AppendObject(GameObject *object)
{
    if (num_objects == MAX_NUM_OBJECTS)
    {
        LOG_ERROR_TRACE("buffer overflow");
        return;
    }

    StateObject &state = states[num_objects];

    state.id = object->params->id;

    UnitObject *unit = object->GetUnitObject();
    GameObjectParameters &param = *unit->params;

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


void MessageCreateGameObject::Compress(Compressor &data) const
{
    data << num_objects;
    data.Write(states,  (uint)sizeof(states[0]) * num_objects);
}


bool MessageCreateGameObject::Decompress(Decompressor &data)
{
    data >> num_objects;
    data.Read(states,   (uint)sizeof(states[0]) * num_objects);

    return true;
}


bool MessageCreateGameObject::HandleMessage(Player *sender) const
{
#ifdef PiCLIENT

    for (int i = 0; i < num_objects; i++)
    {
        const StateObject &state = states[i];

        if (GameObject::objects.Find(state.id))    // Из-за потери пакетов некоторые объекты могут присылаться повторно
        {
            continue;                           // Страхуемся от этого
        }

        if (state.type[0] == (int)TypeGameObject::Unit)
        {
            if (state.type[1] == (int)TypeUnit::Air)
            {
                if (state.type[2] == (int)TypeAirUnit::Airplane)
                {
                    UnitObject *airplane = Airplane::Create(state.id);

                    GameObjectParameters &param = *airplane->params;
                    param.position = state.position;
                    param.direction = state.direction;
                    param.up = state.up;
                    airplane->AppendInGame((int)param.position.x, (int)param.position.y);
                    //                    GameWorld::self->GetRootNode()->AppendNewSubnode(airplane);
                }
                else
                {
                    LOG_ERROR_TRACE("Unknown type air unit");
                }
            }
            else if (state.type[1] == (int)TypeUnit::Ground)
            {
                if (state.type[2] == (int)TypeGroundUnit::Tank)
                {
                    GameObject *tank = Tank::Create(state.id);
                    //                    tank->SetNodeTransform(transform[i]);
                    GameWorld::self->GetRootNode()->AppendNewSubnode(tank);
                }
                else
                {
                    LOG_ERROR_TRACE("Unknown type ground unit");
                }
            }
            else if (state.type[1] == (int)TypeUnit::Water)
            {
                if (state.type[2] == (int)TypeWaterUnit::Submarine)
                {
                    GameObject *submarine = Submarine::Create(state.id);
                    //                    submarine->SetNodeTransform(transform[i]);
                    GameWorld::self->GetRootNode()->AppendNewSubnode(submarine);
                }
                else
                {
                    LOG_ERROR_TRACE("Unknown type water unit");
                }
            }
            else
            {
                LOG_ERROR_TRACE("Unknows type unit");
            }
        }
        else
        {
            LOG_ERROR_TRACE("Unknown type game object");
        }
    }

#endif

    return true;
}


void MessageGameObjectState::AddObject(GameObject *object)
{
    StateObject &state = states[num_objects];

    state.id = object->params->id;

    GameObjectParameters &param = *object->params; //-V522

    state.position = param.position;
    state.direction = param.direction;
    state.up = param.up;

    num_objects++;
}


void MessageGameObjectState::Compress(Compressor &data) const
{
    data << num_objects;
    data.Write(states, (uint)sizeof(states[0]) * num_objects);
}


bool MessageGameObjectState::Decompress(Decompressor &data)
{
    data >> num_objects;
    data.Read(states, (uint)sizeof(states[0]) * num_objects);

    return true;
}


bool MessageGameObjectState::HandleMessage(Player *) const
{
#ifdef PiCLIENT

    if (!GameState::landscapeCreated)
    {
        return true;
    }

    for (int i = 0; i < num_objects; i++)
    {
        const StateObject &state = states[i];

        int _id = state.id;

        GameObject *object = GameObject::objects.Find(_id);

        if (object)
        {
            GameObjectParameters &param = *object->GetUnitObject()->params;
            param.position = state.position;
            param.direction = state.direction;
            param.up = state.up;

            Node *node = object;

            node->SetNodePosition(param.position);
            object->SetDirection(param.direction, param.up);
            object->Invalidate();

            if (object->IsUnit())
            {
                UnitObject *unit = object->GetUnitObject();
                if (unit->params->speed != 0.0f)
                {
                    if (unit->typeUnit == TypeUnit::Air)
                    {
                        AirUnitObject *air = unit->GetAirUnit();
                        if (air->typeAirUnit == TypeAirUnit::Airplane)
                        {
                            Airplane::smokeTrail->CreateSmoke(object->GetNodePosition(), 10000, 0.1f);
                        }
                    }
                }
            }
        }
        else
        {
            TheMessageMgr->SendMessage(PlayerType::Server, MessageRequestCreateGameObject(_id));
        }
    }

#endif

    return true;
}
