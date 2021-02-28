// 2021/02/18 22:31:36 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


//----------------------------------------------------------------------------------------------------------------------
// Здесь хранятся смещения для параметров модели, которые нужно применить к ней для правильной ориентации.
// Масштаб является параметром у node_
class ShiftParameters : public Component
{
    URHO3D_OBJECT(ShiftParameters, Component);

public:

    ShiftParameters(Context *context = TheContext) : Component(context) {}

    static void RegisterObject();

    float rotate = 0.0f;               // Поворот модели относительно направления ноды
    Vector3 position = Vector3::ZERO;  // Если модель не выровнена относительно начала координат, здесь смещение
};


//----------------------------------------------------------------------------------------------------------------------
class GameObject : public LogicComponent
{
    URHO3D_OBJECT(GameObject, LogicComponent);

public:

    void SetPosition(const Vector3 &position);

    static void RegisterObject();

protected:

    GameObject(Context *context);

    void LoadFromJSON(const String &file);

    void Normalize(float k = 1.0f);

    virtual void OnNodeSet(Node *node) override;

private:

    float speed = 0.0f;                     // С такой скоростью объект перемещается

    SharedPtr<StaticModel> staticModel;

    static Vector<GameObject *> storage;

    virtual void FixedUpdate(float time) override = 0;

    Vector3 GetPosition() const;
};
