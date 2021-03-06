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

    float dist = physics.max.SpeedMove() * timeStep;        // ����� ��������

    float delta = (step.endPos - currentPos).Length();      // �������� �� �������� �����

    if (dist >= delta)                                      // ���� ������� ������, ��� �����
    {
        physics.pos.SetWorld(step.endPos);

        return EngineExecutor::Result::Finished;            // �� ��������� ��������� ����
    }

    Vector3 direction = (step.endPos - currentPos);
    direction.Normalize();

    physics.pos.SetWorld(currentPos + direction * dist);

    return Result::Running;
}


static void Calculate(char *name, PhysicsParameters &physics, Step &step)
{
    Vector3 position = physics.pos.GetWorld();
    Vector3 dirToTarget = step.endPos - position;
    dirToTarget.Normalize();                        // ����������� �� ����

    Vector3 direction = physics.dir.GetWorldDir();          // ����������� ������ �����

    float angleNeed = direction.Angle(dirToTarget); // �� ����� ���� ����� ��������� �����

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


EngineExecutor::Result EngineExecutor::ExecuteRotate(PhysicsParameters &physics, float timeStep, EngineT &engine)
{
    PhysicsParameters *pointer = &physics;

    Step &step = engine.algorithm.steps.Front();

    Vector3 dirToTarget = CalcualteDirToTarget(physics, step);

    Vector3 dir = physics.dir.GetWorldDir();

    if (dir.Equals(dirToTarget))
    {
        return Result::Finished;
    }

    Quaternion delta(physics.max.SpeedRotate() * timeStep, { 0.0f, 1.0f, 0.0f });

    physics.rot.ChangeWorld(delta);

    return Result::Running;
}
