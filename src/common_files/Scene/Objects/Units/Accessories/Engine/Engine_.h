// 2021/02/26 21:54:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Units/Accessories/Engine/Logic_.h"


//----------------------------------------------------------------------------------------------------------------------
class EngineParameters : public Object
{
    URHO3D_OBJECT(EngineParameters, Object);

public:

    EngineParameters() : Object(TheContext) {}


};


//----------------------------------------------------------------------------------------------------------------------
class EngineT : public Object
{
    URHO3D_OBJECT(EngineT, Object);

public:

    EngineT(ObjectT *object);
    virtual ~EngineT() {}

    virtual void Update(float timeStep);

    void GiveCommand(CommandEngine::E command);

    // Возвращет true, если мотор заглушен
    bool IsStopped() const;

    EngineCalculator calculator;    // Занимается расчётом алгоритма движения
    EngineAlgorithm  algorithm;     // Собственно алгоритм движения
    EngineExecutor   executor;      // Собственно выполнитель алгоритма движения

    SharedPtr<EngineParameters> params;

protected:

    ObjectT *object = nullptr;
};


//----------------------------------------------------------------------------------------------------------------------
class EngineGround : public EngineT
{
public:

    EngineGround(ObjectT *object) : EngineT(object) {}
};


//----------------------------------------------------------------------------------------------------------------------
class EngineAir : public EngineT
{
public:

    EngineAir(ObjectT *object) : EngineT(object) {}
};
