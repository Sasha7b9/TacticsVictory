// 2021/02/26 21:54:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Components/PhysicsComponent.h"
#include "Scene/Objects/Units/Accessories/Engine/Logic_.h"


//----------------------------------------------------------------------------------------------------------------------
class EngineT : public Component
{
    URHO3D_OBJECT(EngineT, Component);

public:

    EngineT(Context *context) : Component(context) {}

    virtual void Update(float timeStep) { UNUSED(timeStep); };

    void GiveCommand(CommandEngine::E command);

    void OnNodeSet(Node *node) override;

    // Возвращет true, если мотор заглушен
    bool IsStopped() const;

protected:

    SharedPtr<EngineAlgorithm> algorithm;

    EngineExecutor executor;

    SharedPtr<PhysicsComponent> physics;

private:

    EngineCalculator calculator;                // Занимается расчётом алгоритма движения
};


//----------------------------------------------------------------------------------------------------------------------
class EngineAir : public EngineT
{
    URHO3D_OBJECT(EngineAir, EngineT);

public:

    EngineAir(Context *context) : EngineT(context) {}

    virtual void Update(float timeStep) override;

private:
};


//----------------------------------------------------------------------------------------------------------------------
class EngineGround : public EngineT
{
    URHO3D_OBJECT(EngineGround, EngineT);

public:

    EngineGround(Context *context) : EngineT(context) {}

    virtual void Update(float timeStep) override;

    void OnNodeSet(Node *node) override;

    static EngineT *CreateEngine(Node *node);
    
private:
};
