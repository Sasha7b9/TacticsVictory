// 2021/02/18 22:31:36 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


//----------------------------------------------------------------------------------------------------------------------
// ����� �������� �������� ��� ���������� ������, ������� ����� ��������� � ��� ��� ���������� ����������.
// ������� �������� ���������� � node_
class ShiftParameters : public Object
{
    URHO3D_OBJECT(ShiftParameters, Object);

public:

    ShiftParameters() : Object(TheContext) {}

    float rotate = 0.0f;               // ������� ������ ������������ ����������� ����
    Vector3 position = Vector3::ZERO;  // ���� ������ �� ��������� ������������ ������ ���������, ����� ��������
};


//----------------------------------------------------------------------------------------------------------------------
class PhysicsParameters : public Object
{
    URHO3D_OBJECT(PhysicsParameters, Object);

public:

    PhysicsParameters(GameObject *_object) : Object(TheContext), object(_object) {}

    Vector3 GetPosition() const;                // ���������� �������� ������� � ����

private:

    GameObject *object = nullptr;
};


//----------------------------------------------------------------------------------------------------------------------
// ����������� ��� �����/��������� �������� ���������
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

    SharedPtr<ShiftParameters> shift;               // ������������ ��� ���������� ���������� ������ � ������� �����

protected:

    GameObject(Context *context);

    void LoadFromJSON(const String &file);

    void Normalize(float k = 1.0f);

    virtual void OnNodeSet(Node *node) override;

    virtual void Update(float time) override;

private:

    SharedPtr<StaticModel> staticModel;

    static Vector<GameObject *> storage;            // ����� �������� ��� ������� ���� GameObject (� �� ���������)

    SharedPtr<PhysicsParameters> physics;           // ��������� � ���������� ����. ����� ��� ����������

    SharedPtr<GameObjectSpecific> specific;         // ������/������ ����������� ���������
};
