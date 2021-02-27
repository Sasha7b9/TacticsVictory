// 2021/02/26 21:54:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Components/PhysicsComponent.h"


//----------------------------------------------------------------------------------------------------------------------
// Алгоритм действий - результат деятельности EngineCalculator
//
class EngineAlgorithm
{

};


//----------------------------------------------------------------------------------------------------------------------
//  Рассчитывет действия, необходимые произвести, чтобы выполнить команду
//
class EngineCalculator
{

};


//----------------------------------------------------------------------------------------------------------------------
/*
*  Выполняет действия, ранее рассчитанные EngineCalculator
*/
class EngineExecutor
{

};


//----------------------------------------------------------------------------------------------------------------------
class EngineT : public Component
{
    URHO3D_OBJECT(EngineT, Component);

public:

    struct Command { enum E {
        None,
        MoveToNorth,
        MoveToEast,
        MoveToSouth,
        MoveToWest
    }; };

    EngineT(Context *context) : Component(context) {}

    virtual void Update(float timeStep) { UNUSED(timeStep); };

    void GiveCommand(Command::E command);

    void OnNodeSet(Node *node) override;

    // Возвращет true, если мотор заглушен
    bool IsStopped() const;

private:

    SharedPtr<PhysicsComponent> physics;

    EngineCalculator calculator;
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
