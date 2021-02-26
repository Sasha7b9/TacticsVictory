// 2021/02/22 15:41:53 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Scene/Objects/Units/UnitObject_.h"


class Tank;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TankSpecificPart : public Component
{
    URHO3D_OBJECT(TankSpecificPart, Component);

public:

    TankSpecificPart(Context *context) : Component(context) {};

    virtual void OnNodeSet(Node *node) override;

    // ������ �� �������� ���� ����������� ��� ������ ����� (������/������) ������
    static void Create(Node *);
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Tank : public UnitObject
{
friend class TankSpecificPartC;

    URHO3D_OBJECT(Tank, UnitObject);

public:

    Tank(Context *);

    static void RegisterObject();

private:

    // �� ����� �������� ���������� ����� ��������� ��� �� ���� ���������� ��� �������
    virtual void OnNodeSet(Node *node) override;

    // ��� ������� ���������� �� NodeSet
    virtual void Start() override;

    virtual void FixedUpdate(float time) override;

    // ��������� ���� ��������� �������� ���� "Tank"
    static Vector<Tank *> storage;
};
