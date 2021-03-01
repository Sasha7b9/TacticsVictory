// 2021/02/26 21:54:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Units/Accessories/Engine/Logic_.h"


//----------------------------------------------------------------------------------------------------------------------
class EngineParameters : public Component
{
    URHO3D_OBJECT(EngineParameters, Component);

public:

    EngineParameters(Context *context = TheContext) : Component(context) {}

    static void RegisterObject();

    float maxSpeedMove = 0.2f;      // Максимальная скорость движения
    float maxSpeedRotate = 60.0f;   // Максимальная скорость поворота

    Vector3 direction;              // Направление движения
    float speedMove;                // Установившаяся скорость движения
    float accelerationMove;         // Ускорение движения при трогании с места
    Vector3 axisRotate;             // Ось поворота
    float speedRotate;              // Скорость поворота
    float accelerationRotate;       // Ускорение поворота
};


//----------------------------------------------------------------------------------------------------------------------
class EngineT : public Component
{
    URHO3D_OBJECT(EngineT, Component);

public:

    EngineT(Context *context = TheContext);

    static void RegisterObject();

    virtual void OnNodeSet(Node *node) override;

    virtual void Update(float timeStep);

    void GiveCommand(CommandEngine::E command);

    // Возвращет true, если мотор заглушен
    bool IsStopped() const;

    EngineCalculator calculator;    // Занимается расчётом алгоритма движения
    EngineAlgorithm algorithm;      // Собственно алгоритм движения
    EngineExecutor executor;        // Собственно выполнитель алгоритма движения
};
