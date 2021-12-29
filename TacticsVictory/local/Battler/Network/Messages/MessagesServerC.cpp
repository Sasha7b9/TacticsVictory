// 2021/12/21 21:54:25 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Messages/MessagesServer_.h"
#include "Scene/World/Landscape_.h"
#include "TVBattler.h"
#include "Scene/World/GameWorld.h"
#include "Objects/Units/Air/Airplane_.h"
#include "Objects/Units/Ground/Tank_.h"
#include "Objects/Units/Water/Submarine_.h"
#include "GameState.h"
#include "Objects/Units/Unit_.h"
#include "Network/Messages/MessagesClient_.h"

#ifdef PiCLIENT
    #include "Graphics/Effects/SmokeTrail.h"
#endif


using namespace Pi;


bool MessageCreateLandscape::HandleMessage(Player *sender) const
{
    LOG_WRITE("Load landscape %s", name_file.c_str());
    new Landscape((Battler::self->DataPath() + name_file.c_str()).c_str());
    GameWorld::self->GetRootNode()->AppendNewSubnode(Landscape::self);
    Water::Create();

    return true;
}


bool MessageCreateGameObject::HandleMessage(Player *sender) const
{
    for(int i = 0; i < num_objects; i++)
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

                    UnitParameters &param = *airplane->GetUnitController()->param;
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

    return true;
}


bool MessageGameObjectState::HandleMessage(Player *) const
{
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
            UnitParameters &param = *object->GetUnitObject()->GetUnitController()->param;
            param.position = state.position;
            param.direction = state.direction;
            param.up = state.up;

            Node *node = object;

            node->SetNodePosition(param.position);
            object->SetDirection(param.direction, param.up);
            object->Invalidate();

            if(object->IsUnit())
            {
                UnitObject *unit = object->GetUnitObject();
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
        else
        {
            TheMessageMgr->SendMessage(PlayerType::Server, MessageRequestCreateGameObject(_id));
        }
    }

    return true;
}
