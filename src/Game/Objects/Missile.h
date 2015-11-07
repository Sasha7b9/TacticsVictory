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
    float rangeFlying = 150.0f;
    float speed = 10.0f;

    SharedPtr<StaticModel> model;

    void LoadFromFile();
    void Normalize();

    void Init();
};