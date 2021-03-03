// 2021/02/26 21:54:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Units/Accessories/Engine/Logic_.h"


//----------------------------------------------------------------------------------------------------------------------
class EngineParameters : public Object
{
public:

    EngineParameters() : Object(TheContext) {}

    float maxSpeedMove = 1.0f;           // Максимальная скорость движения
    float maxSpeedRotate = 60.0f;       // Максимальная скорость поворота
    float accelerationMove = 1.0f;      // Ускорение движения при трогании с места
    float accelerationRotate = 1.0f;    // Ускорение поворота

    Vector3 direction = Vector3::ONE;   // Направление движения
    float speedMove = 0.0f;             // Установившаяся скорость движения
    Vector3 axisRotate = Vector3::UP;   // Ось поворота
    float speedRotate = 0.0f;           // Скорость поворота
};


//----------------------------------------------------------------------------------------------------------------------
class EngineT : public Object
{
public:

    EngineT() : Object(TheContext) {};
    virtual ~EngineT() {}

    virtual void Update(float timeStep);

    void GiveCommand(CommandEngine::E command);

    // Возвращет true, если мотор заглушен
    bool IsStopped() const;

    EngineCalculator calculator;    // Занимается расчётом алгоритма движения
    EngineAlgorithm algorithm;      // Собственно алгоритм движения
    EngineExecutor executor;        // Собственно выполнитель алгоритма движения

    SharedPtr<EngineParameters> params;

protected:

    Node *node = nullptr;
};


//----------------------------------------------------------------------------------------------------------------------
class EngineGround : public EngineT
{
public:

    EngineGround() : EngineT() {}
};


//----------------------------------------------------------------------------------------------------------------------
class EngineAir : public EngineT
{
public:

    EngineAir() : EngineT() {}
};
