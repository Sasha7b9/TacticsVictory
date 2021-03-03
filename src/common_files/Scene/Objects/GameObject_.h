// 2021/02/18 22:31:36 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


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

    PhysicsParameters(GameObject *_object) : Object(TheContext), object(_object) {}

    Vector3 GetPosition() const;                // Возвращает реальную позицию в мире

private:

    GameObject *object = nullptr;
};


//----------------------------------------------------------------------------------------------------------------------
// Специфичные для клент/серверных объектов параметры
class GameObjectSpecific : public Object
{
    URHO3D_OBJECT(GameObjectSpecific, Object);

public:

    static GameObjectSpecific *Create(GameObject *object);

    virtual void Update(float /*timeStep*/) {};

protected:

    GameObjectSpecific(GameObject *_object) : Object(TheContext), object(_object) {}

    GameObject *object = nullptr;
};


//----------------------------------------------------------------------------------------------------------------------
class GameObject : public LogicComponent
{
    URHO3D_OBJECT(GameObject, LogicComponent);

public:

    void SetPosition(const Vector3 &position);

    SharedPtr<ShiftParameters> shift;               // Используется для приведения параметров модели к текущей сцене

protected:

    GameObject(Context *context);

    void LoadFromJSON(const String &file);

    void Normalize(float k = 1.0f);

    virtual void OnNodeSet(Node *node) override;

    virtual void Update(float time) override;

private:

    SharedPtr<StaticModel> staticModel;

    static Vector<GameObject *> storage;            // Здесь хранятся все объекты типа GameObject (и их подклассы)

    SharedPtr<PhysicsParameters> physics;           // Параметры в физическом мире. Такие как координаты

    SharedPtr<GameObjectSpecific> specific;         // Клиент/сервер специфичные параметры
};
