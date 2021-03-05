// 2021/03/05 20:39:02 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class ObjectT;


struct MovementPP
{
    MovementPP(ObjectT *_object) : object(_object) {}
    Vector3 GetSpeed() const {
        return speedMove;
    };
private:
    ObjectT *object = nullptr;
    Vector3 speedMove = Vector3::ZERO;      // Установившаяся скорость движения
};


struct RotationPP
{
    RotationPP(ObjectT *_object) : object(_object) {}
    Vector3 GetSpeed() const {
        return speedRotate;
    };
private:
    ObjectT *object = nullptr;
    Vector3 speedRotate = Vector3::ZERO;    // Установившаяся скорость вращения
};


struct DirectionPP
{
    DirectionPP(ObjectT *_object) : object(_object) {}
    Vector3 Get() const;                    // Возвращает направление движения (даже если объект неподвижен)
private:
    ObjectT *object = nullptr;
};

struct PositionPP
{
    PositionPP(ObjectT *_object) : object(_object) {}
    Vector3 Get() const;                    // Возвращает реальную позицию в мире
    void Set(const Vector3 &position);      // Устанавливает позицию в мире с учётом смещения
private:
    ObjectT *object = nullptr;
};


struct MaxPP                              // В этой структуре будут храниться максимально возможные значения параметров
{
    float SpeedMove() const {
        return speedMove;
    }
    float SpeedRotate() const {
        return speedRotate;
    }
private:
    float speedMove = 5.0f;                 // Максимальная скорость движения
    float speedRotate = 60.0f;              // Максимальная скорость поворота
};


//----------------------------------------------------------------------------------------------------------------------
class PhysicsParameters : public Object
{
    URHO3D_OBJECT(PhysicsParameters, Object);

public:

    PhysicsParameters(ObjectT *_object) : Object(TheContext),
        position(_object), direction(_object), movement(_object), rotation(_object), object(_object) {}

    MaxPP       max;
    PositionPP  position;
    DirectionPP direction;
    MovementPP  movement;
    RotationPP  rotation;

private:

    ObjectT *object = nullptr;
};
