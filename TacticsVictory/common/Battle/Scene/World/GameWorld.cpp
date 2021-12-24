// 2021/12/20 14:19:15 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/World/GameWorld.h"
#include "Scene/World/Landscape_.h"
#include "TVBattle.h"
#include "Objects/GameObject_.h"
#include "Network/Messages/MessagesServer_.h"


using namespace Pi;


GameWorld *GameWorld::self = nullptr;


GameWorld::GameWorld(pchar name) : World(name)
{
    self = this;
}


GameWorld::~GameWorld()
{

}


WorldResult::B GameWorld::Preprocess()
{
    WorldResult::B result = World::Preprocess();

    if (result != WorldResult::Okay)
    {
        return result;
    }

    new Landscape((Battle::self->DataPath() + "levels/level2.lvl").c_str());

    GetRootNode()->AppendNewSubnode(Landscape::self);

    return WorldResult::Okay;
}


void GameWorld::AppendObject(GameObject *object)
{
    int sizeX = Landscape::self->GetSizeX_Columns();
    int sizeY = Landscape::self->GetSizeY_Rows();

    bool added = false;

    while (!added)
    {
        added = object->AppendInGame(std::rand() % sizeX, std::rand() % sizeY);
    }

    object->controller->Preprocess();
}


void GameWorld::Move()
{
    World::Move();

    static uint64 prevTime = TheTimeMgr->GetMicrosecondCount();

    if (TheTimeMgr->GetMicrosecondCount() - prevTime >= 40000)
    {
        float dT = (float)(TheTimeMgr->GetMicrosecondCount() - prevTime) / 1e3f;

        if (dT > 1000.0f)
        {
            LOG_ERROR_TRACE("dT = %f, prevTime = %llu, microCount = %llu", dT, prevTime, TheTimeMgr->GetMicrosecondCount());
        }

        numTick++;

        RunOneTick();

        prevTime += 40000;
    }
}


void GameWorld::RunOneTick()
{
    for (GameObject *object : GameObject::objects)
    {
        object->controller->Move(40.0f);
    }

    if(TheMessageMgr->GetPlayerCount() > 1)
    {
        MessageGameObjectNodeTransform message;

        for (GameObject *object : GameObject::objects)
        {
            if (message.NumObjects() == message.MaxNumObjects())
            {
                TheMessageMgr->SendMessageClients(message);
                message.ResetCounter();
            }

            message.AddObject(object);
        }

        if (message.NumObjects() > 0)
        {
            TheMessageMgr->SendMessageClients(message);
        }
    }
}
