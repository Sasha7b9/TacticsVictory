// 2021/02/18 22:31:36 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class ObjectT;


//----------------------------------------------------------------------------------------------------------------------
// Здесь хранятся смещения для параметров модели, которые нужно применить к ней для правильной ориентации.
// Масштаб является параметром у node_
class ShiftParameters : public Object
{
    URHO3D_OBJECT(ShiftParameters, Object);

public:

    ShiftParameters() : Object(TheContext) {}

    float rotate = 0.0f;               // Поворот модели относительно направления ноды
    Vector3 position = Vector3::ZERO;  // Если модель не выровнена относительно начала координат, здесь смещение
};


//----------------------------------------------------------------------------------------------------------------------
class PhysicsParameters : public Object
{
    URHO3D_OBJECT(PhysicsParameters, Object);

public:

    PhysicsParameters(ObjectT *_object) : Object(TheContext),
        position(_object), direction(_object), movement(_object), rotation(_object), object(_object) {}

    struct Movement
    {
        Movement(ObjectT *_object) : object(_object) {}
        Vector3 GetSpeed() const { return speedMove; };
    private:
        ObjectT *object = nullptr;
        Vector3 speedMove = Vector3::ZERO;      // Установившаяся скорость движения
    };

    struct Rotation
    {
        Rotation(ObjectT *_object) : object(_object) {}
        Vector3 GetSpeed() const { return speedRotate; };
    private:
        ObjectT *object = nullptr;
        Vector3 speedRotate = Vector3::ZERO;    // Установившаяся скорость вращения
    };

    struct Direction
    {
        Direction(ObjectT *_object) : object(_object) {}
        Vector3 Get() const;                    // Возвращает направление движения (даже если объект неподвижен)
    private:
        ObjectT *object = nullptr;
    };

    struct Position
    {
        Position(ObjectT *_object) : object(_object) {}
        Vector3 Get() const;                    // Возвращает реальную позицию в мире
        void Set(const Vector3 &position);      // Устанавливает позицию в мире с учётом смещения
    private:
        ObjectT *object = nullptr;
    };

    struct Max                          // В этой структуре будут храниться максимально возможные значения параметров
    {
        float SpeedMove() const { return speedMove; }
        float SpeedRotate() const { return speedRotate; }
    private:
        float speedMove = 5.0f;                 // Максимальная скорость движения
        float speedRotate = 60.0f;              // Максимальная скорость поворота
    };

    Max       max;
    Position  position;
    Direction direction;
    Movement  movement;
    Rotation  rotation;

private:

    ObjectT *object = nullptr;
};


//----------------------------------------------------------------------------------------------------------------------
// Специфичные для клент/серверных объектов параметры
class ObjectSpecific : public Object
{
    URHO3D_OBJECT(ObjectSpecific, Object);

public:

    static ObjectSpecific *Create(ObjectT *object);

    virtual void Update(float /*timeStep*/) {};

protected:

    ObjectSpecific(ObjectT *_object);

    ObjectT *object = nullptr;
};


//----------------------------------------------------------------------------------------------------------------------
class ObjectT : public LogicComponent
{
    URHO3D_OBJECT(ObjectT, LogicComponent);

public:

    SharedPtr<ShiftParameters> shift;               // Используется для приведения параметров модели к текущей сцене

    static Vector<ObjectT *> storage;               // Здесь хранятся все объекты типа ObjectT (и их подклассы)

    SharedPtr<PhysicsParameters> physics;           // Параметры в физическом мире. Такие как координаты

    // Упаковать состояние объекта для передачи по сети
    virtual void Compress(VectorBuffer &buffer, bool log = false);

    // Распаковать состояние объекта, принятого по сети
    virtual void Decompress(MemoryBuffer &buffer, bool log = false);

protected:

    ObjectT(Context *context);

    void LoadFromJSON(const String &file);

    void Normalize(float k = 1.0f);

    virtual void OnNodeSet(Node *node) override;

    virtual void Start() override;

    virtual void DelayedStart() override;

    virtual void CreateSpecific() = 0;

    virtual void Update(float time) override;

    // Возвращает глубину вложенности node_ (относительно корневой ноды сцены)
    int NestingDepth();

    SharedPtr<ObjectSpecific> specific;         // Клиент/сервер специфичные параметры

private:

//    Node *GetNode() const { return Component::GetNode(); }

    SharedPtr<StaticModel> staticModel;


public:

    uint GetID() const { return node_->GetID(); }
};
