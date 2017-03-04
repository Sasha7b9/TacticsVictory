#pragma once
#include "Game/Objects/Weapons/WeaponObject.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class RocketLauncher : public WeaponObject
{
    URHO3D_OBJECT(RocketLauncher, WeaponObject);
public:
    RocketLauncher(Context *context = gContext, Tank *tank = nullptr);

    void Init();
    void Update(float deltaStep);

private:
    Tank *tank = nullptr;
    float radiusDetect = 50.0f;
    float timeRecharge = 50.0f;
    float timeElapsedAfterShoot = 0.0f;
    float timePrevRaycast = 0.0f;

    bool TargetInPointView(Tank* tank);

    DEFAULT_MEMBERS(RocketLauncher);
};
