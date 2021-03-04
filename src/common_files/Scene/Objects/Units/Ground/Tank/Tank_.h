// 2021/02/22 15:41:53 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Scene/Objects/Units/Unit_.h"


//----------------------------------------------------------------------------------------------------------------------
class Tank : public Unit
{
    URHO3D_OBJECT(Tank, Unit);

public:

    Tank(Context *);

    static void RegisterComponent();

    virtual void CreateSpecific() override;

    // ��������� ���� ��������� �������� ���� "Tank"
    static Vector<Tank *> storage;

    virtual void Compress(VectorBuffer &buffer) override;

    virtual void Decompress(MemoryBuffer &buffer) override;

private:

    // �� ����� �������� ���������� ����� ��������� ��� �� ���� ���������� ��� �������
    virtual void OnNodeSet(Node *node) override;

    // ��� ������� ���������� �� NodeSet
    virtual void Start() override;

    virtual void Update(float time) override;
};
