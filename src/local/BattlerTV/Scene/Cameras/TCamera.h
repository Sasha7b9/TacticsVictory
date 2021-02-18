/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once


class TCamera
{
public:

    struct Direction { enum E {
        Forward,
        Back,
        Left,
        Right,
        Closer,
        Further,
        RotateYAW,
        RotatePITCH
    }; };

    TCamera();

    void Move(float time);
    void ParallelTranslateLookAt(const Vector3 &lookAt);
    void SetEnabled(bool enabled);
    Vector3 GetPosition();
    void SetPosition(const Vector3 &position);
    void LookAt(const Vector3& lookAt);
    void SetPosition(const Vector3& position, const Vector3& lookAt);
    void DisableArrows() { arrowEnabled = false; };
    void EnableArrows() { arrowEnabled = true; };
    SharedPtr<Node> GetNode();
    Ray GetCursorRay();

private:
    SharedPtr<Node> cameraNode;
    SharedPtr<Light> light;
    Vector3 lookAt;
    float yaw = 10.0f;
    float pitch = 27.0f;
    bool enabled = true;
    bool arrowEnabled = true;

    void SetupViewport();
    void MoveOn(Direction::E direction, float distance);
    void SetPitch(float pitch);
};
