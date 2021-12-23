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
    if (typeGameObject == TypeGameObject::Unit)
    {
        if (typeUnit == TypeUnit::Air)
        {
            if (typeAirUnit == TypeAirUnit::Airplane)
            {
                GameObject *airplane = Airplane::Create(id);
                airplane->SetNodeTransform(transform);
                GameWorld::self->GetRootNode()->AppendNewSubnode(airplane);
            }
            else
            {
                LOG_ERROR_TRACE("Unknown type air unit");
            }
        }
        else if (typeUnit == TypeUnit::Ground)
        {
            if (typeGroundUnit == TypeGroundUnit::Tank)
            {
                GameObject *tank = Tank::Create(id);
                tank->SetNodeTransform(transform);
                GameWorld::self->GetRootNode()->AppendNewSubnode(tank);
            }
            else
            {
                LOG_ERROR_TRACE("Unknown type ground unit");
            }
        }
        else if (typeUnit == TypeUnit::Water)
        {
            if (typeWaterUnit == TypeWaterUnit::Submarine)
            {
                GameObject *submarine = Submarine::Create(id);
                submarine->SetNodeTransform(transform);
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

    return true;
}


bool MessageGameObjectNodeTransform::HandleMessage(Player *) const
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
            GameObjectProperty &property = object->GetGameObjectProperty();

            property.needNewPosition = true;
            property.newPosition = position[i];

//            if (_id == 5)
//            {
//                static uint timePrevUpdate = 0;
//                uint timeUpdate = TheTimeMgr->GetAbsoluteTime();
//
//                uint delta = timeUpdate - timePrevUpdate;
//                timePrevUpdate = timeUpdate;
//
//                static uint prevTime = 0;
//
//                if (TheTimeMgr->GetAbsoluteTime() - prevTime >= 1000)
//                {
//                    prevTime = TheTimeMgr->GetAbsoluteTime();
//
//                    LOG_WRITE("delta = %d ms", delta);
//
//                    LOG_WRITE("in scene %d objects", GameObject::objects.GetElementCount());
//                }
//            }
        }
    }

    return true;
}
