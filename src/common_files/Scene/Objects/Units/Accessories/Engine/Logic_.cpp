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

    Vector3 direction = physics.dir.Get();    // ����������� �������� ������ �����

    Step step(Step::Type::Rotate);

    step.end = dirToTarget;

    algorithm.steps.Push(step);
}


void EngineCalculator::CalculateMovement(PhysicsParameters &physics, CommandEngine::E command, EngineAlgorithm &algorithm)
{
    Step step(Step::Type::Move);

    step.end = physics.pos.Get();

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

    return Result::Finished;
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

    return Result::Running;
}


static void Calculate(char * /*name*/, PhysicsParameters &physics, Step &step)
{
    Vector3 position = physics.pos.Get();
    Vector3 dirToTarget = step.end - position;
    dirToTarget.Normalize();                        // ����������� �� ����

    Vector3 direction = physics.dir.Get();          // ����������� ������ �����

//    float angleNeed = direction.Angle(dirToTarget); // �� ����� ���� ����� ��������� �����

//    LOGINFOF("");
//    LOGINFOF("%s : %f", name, angleNeed);
}


EngineExecutor::Result EngineExecutor::ExecuteRotate(PhysicsParameters &physics, float timeStep, EngineT &engine)
{
    Step &step = engine.algorithm.steps.Front();

    Calculate("before", physics, step);

    Quaternion delta(physics.max.SpeedRotate() * timeStep, { 0.0f, 1.0f, 0.0f });

    physics.rot.Change(delta);

    Calculate("after", physics, step);


//    float angleNeed = direction.Angle(dirToTarget);         // �� ����� ���� ��� ����� �����������, ����� �������� ��
//                                                            // ������� �����
//
//    float angleCan = physics.max.SpeedRotate() * timeStep;  // ������������ ����, �� ������� ����� �����������
//                                                            // � ���� �����
//
//    Vector3 axisRotate = direction.CrossProduct(dirToTarget);
//
//    if (angleCan >= angleNeed)
//    {
//        physics.rot.Set(Quaternion(Vector3::UP, dirToTarget));
//
//        return Result::Finished;
//    }
//    else
//    {
//        Quaternion qutRotate(angleCan, axisRotate);
//
//        physics.rot.Set(Quaternion(Vector3::UP, qutRotate * physics.dir.Get() * physics.mov.GetSpeed()));
//    }

    return Result::Running;
}
