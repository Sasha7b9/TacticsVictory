// 2021/02/26 21:54:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Units/Accessories/Engine/Logic_.h"


//----------------------------------------------------------------------------------------------------------------------
class EngineParameters : public Component
{
    URHO3D_OBJECT(EngineParameters, Component);

public:

    EngineParameters(Context *context = TheContext) : Component(context) {}

    static void RegisterObject();

    float maxSpeedMove = 0.2f;          // ������������ �������� ��������
    float maxSpeedRotate = 60.0f;       // ������������ �������� ��������
    float accelerationMove = 1.0f;      // ��������� �������� ��� �������� � �����
    float accelerationRotate = 1.0f;    // ��������� ��������

    Vector3 direction = Vector3::ONE;   // ����������� ��������
    float speedMove = 0.0f;             // �������������� �������� ��������
    Vector3 axisRotate = Vector3::UP;   // ��� ��������
    float speedRotate = 0.0f;           // �������� ��������
};


//----------------------------------------------------------------------------------------------------------------------
class EngineT : public Component
{
    URHO3D_OBJECT(EngineT, Component);

public:

    EngineT(Context *context = TheContext);

    static void RegisterObject();

    virtual void OnNodeSet(Node *node) override;

    virtual void Update(float timeStep);

    void GiveCommand(CommandEngine::E command);

    // ��������� true, ���� ����� ��������
    bool IsStopped() const;

    EngineCalculator calculator;    // ���������� �������� ��������� ��������
    EngineAlgorithm algorithm;      // ���������� �������� ��������
    EngineExecutor executor;        // ���������� ����������� ��������� ��������
};
