// 2021/02/26 21:54:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Units/Accessories/Engine/Logic_.h"


//----------------------------------------------------------------------------------------------------------------------
class EngineT : public Object
{
    URHO3D_OBJECT(EngineT, Object);

public:

    EngineT(Unit *unit);
    virtual ~EngineT() {}

    virtual void Update(float timeStep);

    void GiveCommand(CommandEngine::E command, int count);

    // Возвращет true, если мотор заглушен
    bool IsStopped() const;

    EngineCalculator calculator;    // Занимается расчётом алгоритма движения
    EngineAlgorithm  algorithm;     // Собственно алгоритм движения
    EngineExecutor   executor;      // Собственно выполнитель алгоритма движения

protected:

    Unit *unit = nullptr;
};


//----------------------------------------------------------------------------------------------------------------------
class EngineGround : public EngineT
{
public:

    EngineGround(Unit *unit) : EngineT(unit) {}
};


//----------------------------------------------------------------------------------------------------------------------
class EngineAir : public EngineT
{
public:

    EngineAir(Unit *unit) : EngineT(unit) {}
};
