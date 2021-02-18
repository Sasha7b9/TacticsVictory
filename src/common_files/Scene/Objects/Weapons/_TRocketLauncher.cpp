// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#ifdef CLIENT
#include "Scene/TCScene.h"
#endif
#include "Scene/_TScene.h"
#include "Scene/Objects/Ammo/Rocket/_TRocket.h"
#include "Scene/Objects/Units/_TTank.h"


RocketLauncher::RocketLauncher(Context *context, Tank *tank) : WeaponObject(context)
{
    this->tank = tank;
}


void RocketLauncher::Init()
{
    timeElapsedAfterShoot = Random(timeRecharge);
}


void RocketLauncher::RegisterInAS()
{
    asIScriptEngine *engine = TheScript->GetScriptEngine();
    engine->RegisterObjectType("RocketLauncher", 0, asOBJ_REF);
#pragma warning(push)
#pragma warning(disable:4191)
    engine->RegisterObjectMethod("RocketLauncher", "void Update(float)", asMETHOD(RocketLauncher, Update), asCALL_THISCALL);
    engine->RegisterObjectBehaviour("RocketLauncher", asBEHAVE_ADDREF, "void AddRef()", asMETHOD(RocketLauncher, AddRef), asCALL_THISCALL);
    engine->RegisterObjectBehaviour("RocketLauncher", asBEHAVE_RELEASE, "void ReleaseRef()", asMETHOD(RocketLauncher, ReleaseRef), asCALL_THISCALL);
#pragma warning(pop)
}


void RocketLauncher::Update(float deltaStep)
{
    if(fabs(timeElapsedAfterShoot) > M_EPSILON)
    {
        timeElapsedAfterShoot += deltaStep;
    }

    if(timeElapsedAfterShoot > timeRecharge)
    {
        for(Tank* target : Tank::GetAll())
        {
            if(target != tank)
            {
                float distance = (tank->GetPosition() - target->GetPosition()).Length();

                if(distance < radiusDetect)
                {
                    if(TargetInPointView(target))
                    {
                        break;
                    }
                }
            }
        }
    }
}


bool RocketLauncher::TargetInPointView(Tank* target)
{
    if(timeElapsedAfterShoot >= timeRecharge && (TheTime->GetElapsedTime() - timePrevRaycast) > 0.5f)
    {
        timePrevRaycast = TheTime->GetElapsedTime();

        Vector3 position = tank->GetNode()->GetComponent<StaticModel>()->GetWorldBoundingBox().Center();
        Vector3 posTarget = target->GetNode()->GetComponent<StaticModel>()->GetWorldBoundingBox().Center();

        Vector3 direction = posTarget - position;
        direction.Normalize();

        Ray ray(position, direction);

        PODVector<RayQueryResult> results;
        RayOctreeQuery query(results, ray, RAY_TRIANGLE, radiusDetect * 2.0f, DRAWABLE_GEOMETRY, VIEW_MASK_FOR_MISSILE);
        TheScene->scene->GetComponent<Octree>()->Raycast(query);

        while(results.Size() && results[0].drawable_->GetNode() == tank->GetNode())
        {
            results.Erase(0, 1);
        }

        if(results.Size() && results[0].drawable_->GetNode() == target->GetNode())
        {
            SharedPtr<Rocket> rocket(Rocket::Create(tank->GetSpeed(), tank->GetPosition(), target));
            timeElapsedAfterShoot = 1e-6f;
            return true;
        }
    }
    return false;
}


void RocketLauncher::RegisterObject()
{
    RegisterInAS();
}
