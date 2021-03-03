// 2021/02/22 15:41:53 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Scene/Objects/Units/UnitObject/UnitObject_.h"


//----------------------------------------------------------------------------------------------------------------------
class TankSpecific : public UnitObjectSpecific
{
    URHO3D_OBJECT(TankSpecific, UnitObjectSpecific);

public:

    TankSpecific(Context *context) : UnitObjectSpecific(context) {};

    // ������ �� �������� ���� ����������� ��� ������ ����� (������/������) ������
    static void Create(Node *);

    virtual void Update(float /*timeStep*/) {};
};


//----------------------------------------------------------------------------------------------------------------------
class Tank : public UnitObject
{
    URHO3D_OBJECT(Tank, UnitObject);

public:

    Tank(Context *);

    static void RegisterObject();

    // ��������� ���� ��������� �������� ���� "Tank"
    static Vector<Tank *> storage;

private:

    // �� ����� �������� ���������� ����� ��������� ��� �� ���� ���������� ��� �������
    virtual void OnNodeSet(Node *node) override;

    // ��� ������� ���������� �� NodeSet
    virtual void Start() override;

    virtual void Update(float time) override;
};
