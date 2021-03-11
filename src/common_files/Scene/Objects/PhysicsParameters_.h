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

    float speedMove = 0.0f;      // ”становивша€с€ скорость движени€
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

    float speedRotate = 0.0f;    // ”становивша€с€ скорость вращени€
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

    Vector3 GetWorld() const;                    // ¬озвращает реальную позицию в мире

    void SetWorld(const Vector3 &position);      // ”станавливает позицию в мире с учЄтом смещени€

private:

    ObjectT *object = nullptr;
};


//----------------------------------------------------------------------------------------------------------------------
struct MaxPP                               // ¬ этой структуре будут хранитьс€ максимально возможные значени€ параметров
{
    MaxPP(float move, float rotate, float alt) : speedMove(move), speedRotate(rotate), altitude(alt) {}

    const float speedMove = 1.0f;                 // ћаксимальна€ скорость движени€
    const float speedRotate = 120.0f;             // ћаксимальна€ скорость поворота
    const float altitude = 10.0f;                 // ћаксимальна€ высота над поверхностью
};


//----------------------------------------------------------------------------------------------------------------------
struct MinPP                                // ¬ этой структуре будут хранитьс€ минимально возможные значени€ параметров
{
    const float altitude = 0.0f;            // ћинимальна€ высота над поверхностью
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
