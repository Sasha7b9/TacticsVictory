// 2021/02/26 21:54:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Units/Accessories/Engine/Logic_.h"


//----------------------------------------------------------------------------------------------------------------------
class EngineParameters : public Object
{
public:

    EngineParameters() : Object(TheContext) {}

    float maxSpeedMove = 1.0f;           // ������������ �������� ��������
    float maxSpeedRotate = 60.0f;       // ������������ �������� ��������
    float accelerationMove = 1.0f;      // ��������� �������� ��� �������� � �����
    float accelerationRotate = 1.0f;    // ��������� ��������

    Vector3 direction = Vector3::ONE;   // ����������� ��������
    float speedMove = 0.0f;             // �������������� �������� ��������
    Vector3 axisRotate = Vector3::UP;   // ��� ��������
    float speedRotate = 0.0f;           // �������� ��������
};


//----------------------------------------------------------------------------------------------------------------------
class EngineT : public Object
{
public:

    EngineT() : Object(TheContext) {};
    virtual ~EngineT() {}

    virtual void Update(float timeStep);

    void GiveCommand(CommandEngine::E command);

    // ��������� true, ���� ����� ��������
    bool IsStopped() const;

    EngineCalculator calculator;    // ���������� �������� ��������� ��������
    EngineAlgorithm algorithm;      // ���������� �������� ��������
    EngineExecutor executor;        // ���������� ����������� ��������� ��������

    SharedPtr<EngineParameters> params;

protected:

    Node *node = nullptr;
};


//----------------------------------------------------------------------------------------------------------------------
class EngineGround : public EngineT
{
public:

    EngineGround() : EngineT() {}
};


//----------------------------------------------------------------------------------------------------------------------
class EngineAir : public EngineT
{
public:

    EngineAir() : EngineT() {}
};
