// 2021/02/26 21:54:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Components/PhysicsComponent.h"
#include "Scene/Objects/Units/Accessories/Engine/Logic_.h"


//----------------------------------------------------------------------------------------------------------------------
class EngineT : public Component
{
    URHO3D_OBJECT(EngineT, Component);

public:

    EngineT(Context *context = TheContext);

    void RegisterObject();

    virtual void OnNodeSet(Node *node) override;

    virtual void Update(float timeStep);

    void GiveCommand(CommandEngine::E command);

    // Возвращет true, если мотор заглушен
    bool IsStopped() const;

protected:

    EngineCalculator calculator;    // Занимается расчётом алгоритма движения
    EngineAlgorithm algorithm;      // Собственно алгоритм движения
    EngineExecutor executor;        // Собственно выполнитель алгоритма движения

    Vector3 speedMove;              // Установившаяся скорость движения
    float accelerationMove;         // Ускорение движения при трогании с места
    Vector3 speedRotate;            // Скорость поворота
    float accelerationRotate;       // Ускорение поворота
    Vector3 currentSpeedMove;       // Текущая скорость движения
    Vector3 currentSpeedRotate;     // Текущая скорость поворота
};
