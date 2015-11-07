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

    float rangeVisible = 50.0f;
    float rangeDistance = 150.0f;
    float absSpeed = 0.0f;
    float rangeTime = 10.0f;

    float time = 0.0f;
    float distance = 0.0f;

    Vector3 position;
    Vector3 speed;

    SharedPtr<StaticModel> model;

    void LoadFromFile();
    void Normalize();

    void Init(const Vector3 &speedShooter, const Vector3 &position);
};