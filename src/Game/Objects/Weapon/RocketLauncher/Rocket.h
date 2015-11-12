#pragma once


#include "Game/Objects/GameObject.h"


class Rocket : public GameObject
{
    URHO3D_OBJECT(Rocket, GameObject);

    friend class ThreadRocket;

public:
    Rocket(Context *context = gContext);
    static void RegisterObject(Context *context = gContext);
    virtual void Update(float) {};
    void UpdateOn();
    static SharedPtr<Rocket> Create(const Vector3 &speedShooter, const Vector3 &position, Tank *target);
    void SetParameters(float timeStep);
    static void UpdateAll(float timeStep);

private:
    Rocket& operator=(const Rocket&)
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
    float rotateSpeed = 90.0f;
    bool firstUpdateEscort = true;

    void Init(const Vector3 &speedShooter, const Vector3 &position, Tank* target);
    void LoadFromFile();
    void Normalize();
    void UpdateBegin();
    void UpdateEscortTarget();
    void CreateSmoke();
    void AnimateSmoke();
    void CalculateAnimate();
    bool VerifyOnIntersectionTerrain();
    void HandlePostRenderUpdate(StringHash, VariantMap&);
    //Vector3 GetPosition();
    //void SetPosition(Vector3 &pos);
    //Mutex mutexPosition;

    float dT;
    bool needCalculate = false;

    BillboardSet *billboardObject = nullptr;
    PODVector<Billboard*> billboards;
    PODVector<float> rotBillboard;

    SharedPtr<ParticleEffect> pe;
    Vector3 scale;

    static Mutex mutexVectorRockets;
};