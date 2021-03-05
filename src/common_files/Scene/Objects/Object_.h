// 2021/02/18 22:31:36 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class ObjectT;


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

    PhysicsParameters(ObjectT *_object) : Object(TheContext),
        position(_object), direction(_object), movement(_object), rotate(_object), object(_object) {}

    struct Movement
    {
        Movement(ObjectT *_object) : object(_object) {}
        Vector3 GetSpeed() const { return speedMove; };
    private:
        ObjectT *object = nullptr;
        Vector3 speedMove = Vector3::ZERO;      // �������������� �������� ��������
    };

    struct Rotate
    {
        Rotate(ObjectT *_object) : object(_object) {}
        Vector3 GetSpeed() const { return speedRotate; };
    private:
        ObjectT *object = nullptr;
        Vector3 speedRotate = Vector3::ZERO;    // �������������� �������� ��������
    };

    struct Direction
    {
        Direction(ObjectT *_object) : object(_object) {}
        Vector3 Get() const;            // ���������� ����������� �������� (���� ���� ������ ����������)
    private:
        ObjectT *object = nullptr;
    };

    struct Position
    {
        Position(ObjectT *_object) : object(_object) {}
        Vector3 Get() const;            // ���������� �������� ������� � ����
    private:
        ObjectT *object = nullptr;
    };

    struct Max                          // � ���� ��������� ����� ��������� ����������� ��������� �������� ����������
    {
        float SpeedMove() const { return speedMove; }
        float SpeedRotate() const { return speedRotate; }
    private:
        float speedMove = 5.0f;             // ������������ �������� ��������
        float speedRotate = 60.0f;          // ������������ �������� ��������
    };

    Max       max;
    Position  position;
    Direction direction;
    Movement  movement;
    Rotate    rotate;

private:

    ObjectT *object = nullptr;
};


//----------------------------------------------------------------------------------------------------------------------
// ����������� ��� �����/��������� �������� ���������
class ObjectSpecific : public Object
{
    URHO3D_OBJECT(ObjectSpecific, Object);

public:

    static ObjectSpecific *Create(ObjectT *object);

    virtual void Update(float /*timeStep*/) {};

protected:

    ObjectSpecific(ObjectT *_object);

    ObjectT *object = nullptr;

    Node *node = nullptr;
};


//----------------------------------------------------------------------------------------------------------------------
class ObjectT : public LogicComponent
{
    URHO3D_OBJECT(ObjectT, LogicComponent);

public:

    void SetPosition(const Vector3 &position);

    SharedPtr<ShiftParameters> shift;               // ������������ ��� ���������� ���������� ������ � ������� �����

    static Vector<ObjectT *> storage;               // ����� �������� ��� ������� ���� ObjectT (� �� ���������)

    SharedPtr<PhysicsParameters> physics;           // ��������� � ���������� ����. ����� ��� ����������

    // ��������� ��������� ������� ��� �������� �� ����
    virtual void Compress(VectorBuffer &buffer, bool log = false);

    // ����������� ��������� �������, ��������� �� ����
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

    // ���������� ������� ����������� node_ (������������ �������� ���� �����)
    int NestingDepth();

    SharedPtr<ObjectSpecific> specific;         // ������/������ ����������� ���������

private:

    SharedPtr<StaticModel> staticModel;
};
