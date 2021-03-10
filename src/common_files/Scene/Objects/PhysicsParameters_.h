// 2021/03/05 20:39:02 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class ObjectT;


//----------------------------------------------------------------------------------------------------------------------
struct MovementPP
{
    MovementPP(ObjectT *_object) : object(_object) {}

    float GetSpeed() const { return speedMove; };

private:

    ObjectT *object = nullptr;

    float speedMove = 0.0f;      // Установившаяся скорость движения
};


//----------------------------------------------------------------------------------------------------------------------
struct RotationPP
{
    RotationPP(ObjectT *_object) : object(_object) {}

    float GetSpeed() const { return speedRotate; };

    Quaternion GetWorld() const;

    void SetWorld(const Quaternion &rotation);

    void ChangeWorld(const Quaternion &delta);

private:

    ObjectT *object = nullptr;

    float speedRotate = 0.0f;    // Установившаяся скорость вращения
};


//----------------------------------------------------------------------------------------------------------------------
struct DirectionPP
{
    DirectionPP(ObjectT *_object) : object(_object) { }

    Vector3 GetWorldDir() const;
    Vector3 GetWorldUp() const;
    Vector3 GetWorldRight() const;

private:

    ObjectT *object = nullptr;
};


//----------------------------------------------------------------------------------------------------------------------
struct PositionPP
{
    PositionPP(ObjectT *_object) : object(_object) {}

    Vector3 GetWorld() const;                    // Возвращает реальную позицию в мире

    void SetWorld(const Vector3 &position);      // Устанавливает позицию в мире с учётом смещения

private:

    ObjectT *object = nullptr;
};


//----------------------------------------------------------------------------------------------------------------------
struct MaxPP                              // В этой структуре будут храниться максимально возможные значения параметров
{
    float SpeedMove() const {  return speedMove; }

    float SpeedRotate() const { return speedRotate; }

private:

    float speedMove = 10.0f;                 // Максимальная скорость движения
    float speedRotate = 360.0f;              // Максимальная скорость поворота
};


//----------------------------------------------------------------------------------------------------------------------
class PhysicsParameters : public Object
{
    URHO3D_OBJECT(PhysicsParameters, Object);

public:

    PhysicsParameters(ObjectT *_object) : Object(TheContext),
        pos(_object), dir(_object), mov(_object), rot(_object), object(_object) {}

    MaxPP       max;
    PositionPP  pos;
    DirectionPP dir;
    MovementPP  mov;
    RotationPP  rot;

private:

    ObjectT *object = nullptr;
};
