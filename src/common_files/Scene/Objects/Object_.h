// 2021/02/18 22:31:36 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/PhysicsParameters_.h"


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
// ����������� ��� �����/��������� �������� ���������
class ObjectSpecific : public Object
{
    URHO3D_OBJECT(ObjectSpecific, Object);

public:

    static ObjectSpecific *Create(ObjectT *object);

    virtual void Update(float /*timeStep*/) {};

    virtual void OnPostRenderUpdate() {};

protected:

    ObjectSpecific(ObjectT *_object);

    ObjectT *object       = nullptr;
};


//----------------------------------------------------------------------------------------------------------------------
class ObjectT : public LogicComponent
{
    URHO3D_OBJECT(ObjectT, LogicComponent);

public:

    // ��������� ��������� ������� ��� �������� �� ����
    virtual void Compress(VectorBuffer &buffer);

    // ����������� ��������� �������, ��������� �� ����
    virtual void Decompress(MemoryBuffer &buffer);

    virtual void OnPostRenderUpdate();

    Node *GetObjectNode() const { return Component::GetNode(); }

    SharedPtr<ShiftParameters>   shift;     // ������������ ��� ���������� ���������� ������ � ������� �����
    static Vector<ObjectT *>     storage;   // ����� �������� ��� ������� ���� ObjectT (� �� ���������)
    SharedPtr<PhysicsParameters> physics;   // ��������� � ���������� ����. ����� ��� ����������
    static ObjectT              *empty;     // ���� ������ ������������ � �������� null-�������

protected:

    ObjectT(Context *context);

    void LoadFromJSON();

    void Normalize(float k = 1.0f);

    virtual void OnNodeSet(Node *node) override;

    virtual void Start() override;

    virtual void DelayedStart() override;

    virtual void CreateSpecific() = 0;

    virtual void Update(float time) override;

    // ���������� ������� ����������� node_ (������������ �������� ���� �����)
    int NestingDepth() const;

    SharedPtr<ObjectSpecific> specific;         // ������/������ ����������� ���������

private:

    // ���������������� ������ � ���� �������� � ����������� �������. ���, ��� ��� ����������, ����� ������������
    // GetObjectNode.
    Node *GetNode() const { return Component::GetNode(); }

    SharedPtr<StaticModel> staticModel;
};
