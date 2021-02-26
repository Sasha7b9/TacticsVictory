// 2021/02/18 22:31:36 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/GameObjectSpecificPart_.h"


class GameObject : public LogicComponent
{
    URHO3D_OBJECT(GameObject, LogicComponent);

public:

    void SetPosition(const Vector3 &position);

protected:

    struct Type { enum E {
        Client,
        Server
    }; };

    GameObject(Context *context);

    void LoadFromJSON(const String &file);

    void Normalize(float k = 1.0f);

    static const Type::E type;

private:

    float speed = 0.0f;                     // � ����� ��������� ������ ������������
    float shiftRotate = 0.0f;               // ������� ������ ������������ ����������� ����
    Vector3 shiftPosition = Vector3::ZERO;  // ���� ������ �� ��������� ������������ ������ ���������, ����� ��������

    SharedPtr<StaticModel> staticModel;

    static Vector<GameObject *> storage;

    virtual void FixedUpdate(float time) override = 0;

    Vector3 GetPosition() const;

    SharedPtr<GameObjectSpecificPart> specificObject;
};
