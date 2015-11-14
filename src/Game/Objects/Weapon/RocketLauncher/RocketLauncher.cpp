#include <stdafx.h>


#include "RocketLauncher.h"
#include "Game/Objects/Units/Tank/Tank.h"
#include "Game/Objects/GameObjectEvents.h"
#include "Game/Objects/Weapon/RocketLauncher/Rocket.h"


RocketLauncher::RocketLauncher(Context *context, Tank *tank) :
    Object(context)
{
    this->tank = tank;

    return;

    Node* nodeCameraTarget = gScene->CreateChild("CameraTarget");
    cameraTarget = nodeCameraTarget->CreateComponent<Camera>();
    cameraTarget->SetNearClip(0.5f);
    cameraTarget->SetFarClip(radiusDetect);

    renderTexture = new Texture2D(gContext);
    renderTexture->SetSize(SIZE_WINDOW_TARGET, SIZE_WINDOW_TARGET, Graphics::GetRGBFormat(), Urho3D::TEXTURE_RENDERTARGET);
    renderTexture->SetFilterMode(Urho3D::FILTER_DEFAULT);

    renderSurface = renderTexture->GetRenderSurface();
    SharedPtr<Viewport> viewport(new Viewport(gContext, gScene, cameraTarget));
    renderSurface->SetViewport(0, viewport);
    
    renderSurface->SetUpdateMode(Urho3D::SURFACE_UPDATEALWAYS);

    SubscribeToEvent(Urho3D::E_POSTRENDERUPDATE, URHO3D_HANDLER(RocketLauncher, HandlePostRenderUpdate));
}

void RocketLauncher::Init()
{
    timeElapsedAfterShoot = Random(timeRecharge);
}

void RocketLauncher::Update(float deltaStep)
{
    if(timeElapsedAfterShoot != 0.0f)
    {
        timeElapsedAfterShoot += deltaStep;
    }

    if(timeElapsedAfterShoot > timeRecharge)
    {
        for(auto target : gTanks)
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
    if(timeElapsedAfterShoot >= timeRecharge)
    {
        Vector3 position = tank->GetNode()->GetComponent<StaticModel>()->GetWorldBoundingBox().Center();
        Vector3 posTarget = target->GetNode()->GetComponent<StaticModel>()->GetWorldBoundingBox().Center();

        Vector3 direction = posTarget - position;
        direction.Normalize();

        Ray ray(position, direction);

        PODVector<RayQueryResult> results;
        RayOctreeQuery query(results, ray, Urho3D::RAY_TRIANGLE, radiusDetect * 2.0f, Urho3D::DRAWABLE_GEOMETRY, VIEW_MASK_FOR_MISSILE);
        gScene->GetComponent<Octree>()->Raycast(query);

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

void RocketLauncher::HandlePostRenderUpdate(StringHash, VariantMap&)
{
    if(tank->IsSelected())
    {
        cameraTarget->GetNode()->SetPosition(tank->GetPosition() + Vector3(0.0f, 0.2f, 0.0f));
        cameraTarget->GetNode()->SetRotation(tank->GetNode()->GetRotation());

        VariantMap eventData = GetEventDataMap();
        eventData[GameObjectEvent::P_TEXTURE] = renderTexture;
        SendEvent(E_SETTEXTURE, eventData);
    }
}
