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
    Vector3 position = physics.pos.Get();

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

    Vector3 dirToTarget = target - position;                // ����������� �� �����, � ������� ����� ��������� �������
    dirToTarget.Normalize();

    Vector3 direction = physics.direction.Get();    // ����������� �������� ������ �����

    Step step(Step::Type::Rotate);

    step.start = direction;
    step.end = dirToTarget;

    algorithm.steps.Push(step);
}


void EngineCalculator::CalculateMovement(PhysicsParameters &physics, CommandEngine::E command, EngineAlgorithm &algorithm)
{
    Step step(Step::Type::Move);

    step.start = physics.pos.Get();
    step.end = step.start;

    switch (command)
    {
    case CommandEngine::MoveToNorth:    step.end.x_ -= 1.0f;    break;
    case CommandEngine::MoveToEast:     step.end.z_ += 1.0f;    break;
    case CommandEngine::MoveToSouth:    step.end.x_ += 1.0f;    break;
    case CommandEngine::MoveToWest:     step.end.z_ -= 1.0f;    break;
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

    return EngineExecutor::Result::Finished;
}


EngineExecutor::Result EngineExecutor::ExecuteMovement(PhysicsParameters &physics, float timeStep, EngineT &engine)
{
    Step &step = engine.algorithm.steps.Front();

    Vector3 currentPos = physics.pos.Get();

    float dist = physics.max.SpeedMove() * timeStep;        // ����� ��������

    float delta = (step.end - currentPos).Length();         // �������� �� �������� �����

    if (dist >= delta)                                      // ���� ������� ������, ��� �����
    {
        physics.pos.Set(step.end);

        return EngineExecutor::Result::Finished;            // �� ��������� ��������� ����
    }

    Vector3 direction = (step.end - currentPos);
    direction.Normalize();

    physics.pos.Set(currentPos + direction * dist);

    return EngineExecutor::Result(EngineExecutor::Result::Running);
}


EngineExecutor::Result EngineExecutor::ExecuteRotate(PhysicsParameters &physics, float timeStep, EngineT &engine)
{
    Step &step = engine.algorithm.steps.Front();

    Vector3 position = physics.pos.Get();

    Vector3 dirToTarget = step.end - position;              // ����������� �� �����, � ������� ����� ��������� �������
    dirToTarget.Normalize();

    Vector3 direction = physics.direction.Get();            // ���� ������� ��� ����

    float angleNeed = direction.Angle(dirToTarget);         // �� ����� ���� ��� ����� �����������, ����� �������� ��
                                                            // ������� �����

    float angleCan = physics.max.SpeedRotate() * timeStep;  // ������������ ����, �� ������� ����� �����������
                                                            // � ���� �����

    if (angleCan >= angleNeed)
    {
        
    }
    else
    {

    }

    return EngineExecutor::Result::Finished;
}
