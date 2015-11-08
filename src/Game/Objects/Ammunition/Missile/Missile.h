#pragma once


#include "Game/Objects/GameObject.h"


class Missile : public GameObject
{
    OBJECT(Missile);

public:
    Missile(Context *context = gContext);
    static void RegisterObject(Context *context = gContext);
    virtual void Update(float timeStep);
    static SharedPtr<Missile> Create(const Vector3 &speedShooter, const Vector3 &position, Tank *target);

private:
    Missile& operator=(const Missile&)
    {};

    Tank *target = nullptr;
    SharedPtr<StaticModel> model;

    enum State
    {
        Begin,              // The missile is in this state from the start-up moment before achievement of heightBeginExcortTarget
        EscortTarget
    } state = Begin;

    const float rangeVisible = 50.0f;
    const float rangeDistance = 250.0f;
    const float rangeTime = 60.0f;
    const float heightBeginExcortTarget = 5.0f;

    float time = 0.0f;
    float distance = 0.0f;

    // Current state
    Vector3 position;
    Vector3 speed;
    Quaternion rotate;
    float absSpeed = 0.0f;
    float rotateSpeed = 20.0f;
    bool firstUpdateEscort = true;

    void Init(const Vector3 &speedShooter, const Vector3 &position, Tank* target);
    void LoadFromFile();
    void Normalize();
    void UpdateBegin(float dT);
    void UpdateEscortTarget(float dT);
    void CreateSmoke();
    void AnimateSmoke(float timeStep);

    void HandlePostRenderUpdate(StringHash, VariantMap&);
};