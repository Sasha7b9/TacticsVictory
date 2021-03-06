// 2021/02/27 10:04:52 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Object_.h"
#include "Scene/Objects/Units/Accessories/Engine/Engine_.h"
#include "Scene/Objects/Units/Accessories/Engine/Logic_.h"


void EngineCalculator::Calculate(PhysicsParameters &physics, CommandEngine::E command, EngineAlgorithm &algorithm)
{
    CalculateRotate(physics, command, algorithm);

    CalculateMovement(physics, command, algorithm);
}


void EngineCalculator::CalculateRotate(PhysicsParameters &physics, CommandEngine::E command, EngineAlgorithm & algorithm)
{
    Vector3 position = physics.pos.GetWorld();

    Vector3 target = position;

    switch (command)
    {
    case CommandEngine::MoveToNorth:    target.x_ -= 1.0f;      break;
    case CommandEngine::MoveToEast:     target.z_ += 1.0f;      break;
    case CommandEngine::MoveToSouth:    target.x_ += 1.0f;      break;
    case CommandEngine::MoveToWest:     target.z_ -= 1.0f;      break;
    case CommandEngine::None:
        break;
    }

    Step step(Step::Type::Rotate);

    step.endPos = target;

    algorithm.steps.Push(step);
}


void EngineCalculator::CalculateMovement(PhysicsParameters &physics, CommandEngine::E command, EngineAlgorithm &algorithm)
{
    Step step(Step::Type::Move);

    step.endPos = physics.pos.GetWorld();

    switch (command)
    {
    case CommandEngine::MoveToNorth:    step.endPos.x_ -= 1.0f;    break;
    case CommandEngine::MoveToEast:     step.endPos.z_ += 1.0f;    break;
    case CommandEngine::MoveToSouth:    step.endPos.x_ += 1.0f;    break;
    case CommandEngine::MoveToWest:     step.endPos.z_ -= 1.0f;    break;
    case CommandEngine::None:
        break;
    }

    algorithm.steps.Push(step);
}


EngineExecutor::Result EngineExecutor::Execute(PhysicsParameters &physics, float timeStep, EngineT &engine)
{
    if (engine.algorithm.IsFinished())
    {
        return EngineExecutor::Result::Finished;
    }

    switch (engine.algorithm.steps.Front().type)
    {
    case Step::Type::Move:      return ExecuteMovement(physics, timeStep, engine);   break;
    case Step::Type::Rotate:    return ExecuteRotate(physics, timeStep, engine);     break;
    case Step::Type::None:
        break;
    }

    return Result::Finished;
}


EngineExecutor::Result EngineExecutor::ExecuteMovement(PhysicsParameters &physics, float timeStep, EngineT &engine)
{
    Step &step = engine.algorithm.steps.Front();

    Vector3 currentPos = physics.pos.GetWorld();

    float dist = physics.max.SpeedMove() * timeStep;        // Нужно проехать

    float delta = (step.endPos - currentPos).Length();      // Осталось до конечной точки

    if (dist >= delta)                                      // Если проедем больше, чем нужно
    {
        physics.pos.SetWorld(step.endPos);

        return EngineExecutor::Result::Finished;            // То завершаем выполение шага
    }

    physics.pos.SetWorld(currentPos + physics.dir.GetWorldDir() * dist);

    return Result::Running;
}


static void Calculate(char *name, PhysicsParameters &physics, Step &step)
{
    Vector3 position = physics.pos.GetWorld();
    Vector3 dirToTarget = step.endPos - position;
    dirToTarget.Normalize();                        // Направление на цель

    Vector3 direction = physics.dir.GetWorldDir();          // Направление нашего юнита

    float angleNeed = direction.Angle(dirToTarget); // На такой угол нужно повернуть юнита

    LOGINFOF("");
    LOGINFOF("%s : %f", name, angleNeed);
}


Vector3 CalcualteDirToTarget(PhysicsParameters &physics, Step &step)
{
    Vector3 position = physics.pos.GetWorld();
    Vector3 dirToTarget = step.endPos - position;
    dirToTarget.Normalize();
    return dirToTarget;
}


static float CalculateDelta(PhysicsParameters &physics, Step &step)
{
    Vector3 dirToTarget = CalcualteDirToTarget(physics, step);

    Vector3 dir = physics.dir.GetWorldDir();

    return (dir - dirToTarget).Length();
}


EngineExecutor::Result EngineExecutor::ExecuteRotate(PhysicsParameters &physics, float dT, EngineT &engine)
{
    Vector3 &endPos = engine.algorithm.GetStep().endPos;            // К этой точке нужно повернуться

    Vector3 dir = physics.dir.GetWorldDir();                        // Направление движения юнита

    Vector3 dirToEndPos = endPos - physics.pos.GetWorld();
    dirToEndPos.Normalize();                                        // Направление на цель

    float angleNeed = dir.Angle(dirToEndPos);

    float angleCan = physics.max.SpeedRotate() * dT;

    Vector3 axixRotate = dir.CrossProduct(dirToEndPos);

    if (angleCan < angleNeed)                       // Если за этот фрейм не получится полностью повернуться
    {
        Quaternion delta(angleCan, axixRotate);
        physics.rot.ChangeWorld(delta);
        return Result::Running;
    }

    physics.rot.ChangeWorld(Quaternion(angleNeed, axixRotate));

    return Result::Finished;
}
