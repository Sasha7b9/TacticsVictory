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

    // Возвращает реальную позицию в мире
    Vector3 GetWorld() const;

    // Устанавливает позицию в мире с учётом смещения
    void SetWorld(const Vector3 &position);

    // Возвращает высоту объекта (координата y)
    float GetAltitude() const { return GetWorld().y_; }

    // Возвращает координаты объекта в пространстве карты
    Vector2 GetCoord() const;

    // Эта функция рассчитывает дистанцию от центра
    void CalculateDistanceFromCenter() { distanceFromCenter = GetWorld().LengthSquared(); }

    float distanceFromCenter = 0.0f;        // Дистанция от центра

private:

    ObjectT *object = nullptr;
};


//----------------------------------------------------------------------------------------------------------------------
struct MaxPP                               // В этой структуре будут храниться максимально возможные значения параметров
{
    const float speedMove = 1.0f;                 // Максимальная скорость движения
    const float speedRotate = 120.0f;             // Максимальная скорость поворота
    const float altitude = 10.0f;                 // Максимальная высота над поверхностью
};


//----------------------------------------------------------------------------------------------------------------------
struct MinPP                                // В этой структуре будут храниться минимально возможные значения параметров
{
    const float altitude = 0.0f;            // Минимальная высота над поверхностью
};


//----------------------------------------------------------------------------------------------------------------------
class PhysicsParameters : public Object
{
    URHO3D_OBJECT(PhysicsParameters, Object);

public:

#undef min
#undef max

    PhysicsParameters(ObjectT *_object, const MinPP &_min, const MaxPP &_max) : Object(TheContext),
        min(_min), max(_max), pos(_object), dir(_object), mov(_object), rot(_object), object(_object) {}

    MinPP       min;
    MaxPP       max;
    PositionPP  pos;
    DirectionPP dir;
    MovementPP  mov;
    RotationPP  rot;

private:

    ObjectT *object = nullptr;
};
