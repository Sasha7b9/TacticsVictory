// 2021/02/18 22:31:36 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class GameObject : public LogicComponent
{
    URHO3D_OBJECT(GameObject, LogicComponent);

public:

    virtual void FixedUpdate(float time) override = 0;

    static Vector<GameObject *> storage;

    Vector3 GetPosition() const;

    void SetPosition(const Vector3 &position);

protected:

    void LoadFromJSON(const String &file);

    void Normalize(float k = 1.0f);

    GameObject(Context *context);

private:

    SharedPtr<StaticModel> staticModel;

    float speed = 0.0f;                     // С такой скоростью объект перемещается
    float shiftRotate = 0.0f;               // Поворот модели относительно направления ноды
    Vector3 shiftPosition = Vector3::ZERO;  // Если модель не выровнена относительно начала координат, здесь смещение
};
