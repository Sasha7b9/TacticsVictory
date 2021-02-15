/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "Game/Objects/Ammo/AmmoObject.h"



class Rocket : public AmmoObject
{
    URHO3D_OBJECT(Rocket, AmmoObject);

    friend class ThreadRocket;

public:
    Rocket(Context *context = gContext);
    ~Rocket();

    static void RegisterObject(Context *context = gContext);

    void UpdateOn();
    static SharedPtr<Rocket> Create(const Vector3 &speedShooter, const Vector3 &position, Tank *target);
    void SetParameters(float timeStep);
    static void StopAllThreads();
    static void UpdateAll(float timeStep);
    static void DeleteAll();

private:
    enum State
    {
        Begin,              // The missile is in this state from the start-up moment before achievement of heightBeginExcortTarget
        EscortTarget
    } state = Begin;

    Tank *target = nullptr; //-V122
    SharedPtr<StaticModel> model;

    const float rangeVisible = 50.0f;
    const float rangeTime = 60.0f;
    const float heightBeginExcortTarget = 2.0f;
    const float rotateSpeed = 90.0f;
    const float startSpeedKoeff = 1.5f;

    float timePrevRaycast = 0.0f;

    // Current state
    Vector3 position;
    Vector3 speed;
    Quaternion rotate;
    float time = 0.0f;
    float absSpeed = 0.0f;
    Tank *attackedUnit = nullptr; //-V122
    bool collisionWithTerrain = false;

    float dT = 0.0f;

    BillboardSet *billboardObjectSmoke = nullptr; //-V122
    PODVector<Billboard*> billboardsSmoke;
    PODVector<float> rotBillboardSmoke;
    SharedPtr<ParticleEffect> pe;
    Vector3 scale;
    Node *smokeNode = nullptr; //-V122

    Mutex mutex;
    bool isCalculated = false;

    void Init(const Vector3 &speedShooter, const Vector3 &position, Tank* target);
    void LoadFromFile();
    void Normalize();
    void UpdateBegin();
    void UpdateEscortTarget();
    void CreateSmoke();
    void AnimateSmoke();
    void CalculateAnimate();
    void VerifyOnIntersectionTerrain();
    void HandlePostRenderUpdate(StringHash, VariantMap&);

    DEFAULT_MEMBERS(Rocket);
};
