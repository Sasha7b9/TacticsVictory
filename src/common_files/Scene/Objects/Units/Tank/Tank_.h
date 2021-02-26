// 2021/02/22 15:41:53 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Scene/Objects/Units/UnitObject/UnitObject_.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TankSpecific : public Component
{
public:

    TankSpecific(Context *context) : Component(context) {};

    // ������ �� �������� ���� ����������� ��� ������ ����� (������/������) ������
    static void Create(Node *);
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Tank : public UnitObject
{
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

    virtual void FixedUpdate(float time) override;
};
