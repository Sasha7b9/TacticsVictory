// 2021/02/26 21:54:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Components/PhysicsComponent.h"
#include "Scene/Objects/Units/Accessories/Engine/Logic_.h"


//----------------------------------------------------------------------------------------------------------------------
class EngineT : public Component
{
    URHO3D_OBJECT(EngineT, Component);

public:

    EngineT(Context *context = TheContext);

    void RegisterObject();

    virtual void OnNodeSet(Node *node) override;

    virtual void Update(float timeStep);

    void GiveCommand(CommandEngine::E command);

    // ��������� true, ���� ����� ��������
    bool IsStopped() const;

protected:

    EngineCalculator calculator;    // ���������� �������� ��������� ��������
    EngineAlgorithm algorithm;      // ���������� �������� ��������
    EngineExecutor executor;        // ���������� ����������� ��������� ��������

    Vector3 speedMove;              // �������������� �������� ��������
    float accelerationMove;         // ��������� �������� ��� �������� � �����
    Vector3 speedRotate;            // �������� ��������
    float accelerationRotate;       // ��������� ��������
    Vector3 currentSpeedMove;       // ������� �������� ��������
    Vector3 currentSpeedRotate;     // ������� �������� ��������
};
