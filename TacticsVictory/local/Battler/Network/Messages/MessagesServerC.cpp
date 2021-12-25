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
        if (type[i][0] == (int)TypeGameObject::Unit)
        {
            if (type[i][1] == (int)TypeUnit::Air)
            {
                if (type[i][2] == (int)TypeAirUnit::Airplane)
                {
                    GameObject *airplane = Airplane::Create(id[i]);
                    airplane->SetNodeTransform(transform[i]);
                    GameWorld::self->GetRootNode()->AppendNewSubnode(airplane);
                }
                else
                {
                    LOG_ERROR_TRACE("Unknown type air unit");
                }
            }
            else if (type[i][1] == (int)TypeUnit::Ground)
            {
                if (type[i][2] == (int)TypeGroundUnit::Tank)
                {
                    GameObject *tank = Tank::Create(id[i]);
                    tank->SetNodeTransform(transform[i]);
                    GameWorld::self->GetRootNode()->AppendNewSubnode(tank);
                }
                else
                {
                    LOG_ERROR_TRACE("Unknown type ground unit");
                }
            }
            else if (type[i][1] == (int)TypeUnit::Water)
            {
                if (type[i][2] == (int)TypeWaterUnit::Submarine)
                {
                    GameObject *submarine = Submarine::Create(id[i]);
                    submarine->SetNodeTransform(transform[i]);
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
        int _id = id[i];
        GameObject *object = GameObject::objects.Find(_id);

        if (object)
        {
            UnitParameters &param = object->GetUnitObject()->GetUnitController()->param;
            param.direction = direction[i];
            param.up = up[i];

            object->SetNodePosition(position[i]);
            object->SetDirection(param.direction, param.up);
            object->Invalidate();
        }
        else
        {
            TheMessageMgr->SendMessage(PlayerType::Server, MessageRequestCreateGameObject(_id));
        }
    }

    return true;
}
