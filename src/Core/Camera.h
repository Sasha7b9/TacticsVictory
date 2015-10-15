#pragma once


class tvCamera
{
public:
    enum Direction
    {
        Direction_Forward,
        Direction_Back,
        Direction_Left,
        Direction_Right,
        Direction_Closer,
        Direction_Further,
        Direction_RotateYAW,
        Direction_RotatePITCH
    };
    tvCamera();

    void RotateOn(float yaw, float pitch);
    void Move(float time);
    void SetEnabled(bool enabled);
    Vector3 GetPosition();
    void SetPosition(const Vector3 &position);
    void LookAt(const Vector3& lookAt);
    void SetPosition(const Vector3& position, const Vector3& lookAt);
    SharedPtr<Node> GetNode();

private:
    void SetupViewport();
    void MoveOn(Direction direction, float distance);
    void SetPitch(float pitch);

    SharedPtr<Node> cameraNode;
    float yaw = 76.0f;
    float pitch = 28.0f;
    SharedPtr<Light> light;
    bool enabled = false;
    Vector3 lookAt;
};