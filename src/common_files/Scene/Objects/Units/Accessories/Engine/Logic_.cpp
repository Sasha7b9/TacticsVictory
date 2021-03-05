// 2021/02/27 10:04:52 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Object_.h"
#include "Scene/Objects/Units/Accessories/Engine/Engine_.h"
#include "Scene/Objects/Units/Accessories/Engine/Logic_.h"


void EngineCalculator::Calculate(ObjectT *object, CommandEngine::E command, EngineAlgorithm &algorithm)
{
    CalculateRotate(object, command, algorithm);

    CalculateMovement(object, command, algorithm);
}


void EngineCalculator::CalculateRotate(ObjectT *object, CommandEngine::E command, EngineAlgorithm & algorithm)
{
//    float yaw = node->GetRotation().YawAngle();

    Vector3 position = object->GetNode()->GetPosition();

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

    Vector3 dirToTarget = target - position;                // Направление на точку, к которой нужно совершить поворот
    dirToTarget.Normalize();

    Vector3 direction = object->physics->direction.Get();    // Направление движения нашего юнита

    Step step(Step::Type::Rotate);

    step.start = direction;
    step.end = dirToTarget;

    algorithm.steps.Push(step);
}


void EngineCalculator::CalculateMovement(ObjectT *object, CommandEngine::E command, EngineAlgorithm &algorithm)
{
    Step step(Step::Type::Move);

    step.start = object->GetNode()->GetPosition();
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


EngineExecutor::Result EngineExecutor::Execute(ObjectT *object, float timeStep, EngineT &engine)
{
    if (engine.algorithm.IsFinished())
    {
        return EngineExecutor::Result::Finished;
    }

    switch (engine.algorithm.steps.Front().type)
    {
    case Step::Type::Move:      return ExecuteMovement(object, timeStep, engine);   break;
    case Step::Type::Rotate:    return ExecuteRotate(*object->physics, timeStep, engine);     break;
    case Step::Type::None:
        break;
    }

    return EngineExecutor::Result::Finished;
}


EngineExecutor::Result EngineExecutor::ExecuteMovement(ObjectT *object, float timeStep, EngineT &engine)
{
    Step &step = engine.algorithm.steps.Front();

    Vector3 currentPos = object->GetNode()->GetPosition();

    float dist = object->physics->max.SpeedMove() * timeStep;    // Нужно проехать

    float delta = (step.end - currentPos).Length();         // Осталось до конечной точки

    if (dist >= delta)                                      // Если проедем больше, чем нужно
    {
        object->GetNode()->SetPosition(step.end);

        return EngineExecutor::Result::Finished;            // То завершаем выполение шага
    }

    Vector3 direction = (step.end - currentPos);
    direction.Normalize();

    object->GetNode()->SetPosition(currentPos + direction * dist);

    return EngineExecutor::Result(EngineExecutor::Result::Running);
}


EngineExecutor::Result EngineExecutor::ExecuteRotate(PhysicsParameters &physics, float timeStep, EngineT &engine)
{
    Step &step = engine.algorithm.steps.Front();

    Vector3 position = physics.position.Get();

    Vector3 dirToTarget = step.end - position;              // Направление на точку, к которой нужно совершить поворот
    dirToTarget.Normalize();

    Vector3 direction = physics.direction.Get();            // Сюда нацелен наш юнит

    float angleNeed = direction.Angle(dirToTarget);         // На такой угол нам нужно повернуться, чтобы смотреть на
                                                            // целевую точку

    float angleCan = physics.max.SpeedRotate() * timeStep;  // Максимальный угол, на который можно повернуться
                                                            // в этом кадре

    if (angleCan >= angleNeed)
    {

    }

    return EngineExecutor::Result::Finished;
}
