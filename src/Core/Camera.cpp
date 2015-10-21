#include <stdafx.h>


#include "Camera.h"
#include "GUI/Elements/Cursor.h"
#include "GUI/GUI.h"


lCamera::lCamera()
{
    cameraNode = gScene->CreateChild("Camera");

    Camera *camera = cameraNode->CreateComponent<Camera>();
    camera->SetFarClip(1000.0f);
    camera->SetNearClip(1.0f);
    cameraNode->SetRotation(Quaternion(pitch, yaw, 0.0f));
    cameraNode->SetPosition({-37.0f, 45.0f, 15.0f});

    light = cameraNode->CreateComponent<Light>();
    light->SetLightType(Urho3D::LIGHT_POINT);
    light->SetRange(100.0f);
    light->SetEnabled(false);

    SetupViewport();
}

Vector3 lCamera::GetPosition()
{
    return cameraNode->GetPosition();
}

void lCamera::SetPosition(const Vector3 &position)
{
    cameraNode->SetPosition(position);
}

void lCamera::SetPosition(const Vector3& position, const Vector3& lookAt_)
{
    cameraNode->SetPosition(position);
    lookAt = lookAt_;
    cameraNode->LookAt(lookAt);
}

void lCamera::RotateOn(float _yaw, float _pitch)
{
    if (enabled)
    {
        yaw += _yaw;
        pitch += _pitch;
        cameraNode->SetRotation(Quaternion(pitch, yaw, 0.0f));
    }
}

void lCamera::SetYAW(float _yaw)
{
    if (enabled)
    {
        Vector3 deltaPos = cameraNode->GetPosition();
        cameraNode->SetPosition(Vector3::ZERO);

        yaw = _yaw;
        cameraNode->SetRotation(Quaternion(pitch, yaw, 0.0f));

        cameraNode->SetPosition(-deltaPos);
    }
}

void lCamera::LookAt(const Vector3 &lookAt_)
{
    Vector3 delta = lookAt_ - lookAt;

    lookAt = lookAt_;
    cameraNode->LookAt(lookAt);
    cameraNode->SetPosition(cameraNode->GetPosition() + delta);
}

void lCamera::Move(float time)
{
    if(!enabled)
    {
        return;
    }

    const float MOVE_SPEED = 30.0f;

    float distance = MOVE_SPEED * time;

    TypeCursor cursor = gCursor->GetType();

    if(cursor == TypeCursor_Up || cursor == TypeCursor_TopLeft || cursor == TypeCursor_TopRight || gInput->GetKeyDown(Urho3D::KEY_UP))
    {
        MoveOn(Direction_Forward, distance);
    }
    if(cursor == TypeCursor_Down || cursor == TypeCursor_DownLeft || cursor == TypeCursor_DownRight || gInput->GetKeyDown(Urho3D::KEY_DOWN))
    {
        MoveOn(Direction_Back, distance);
    }
    if(cursor == TypeCursor_Left || cursor == TypeCursor_TopLeft || cursor == TypeCursor_DownLeft || gInput->GetKeyDown(Urho3D::KEY_LEFT))
    {
        MoveOn(Direction_Left, distance);
    }
    if(cursor == TypeCursor_Right || cursor == TypeCursor_TopRight || cursor == TypeCursor_DownRight || gInput->GetKeyDown(Urho3D::KEY_RIGHT))
    {
        MoveOn(Direction_Right, distance);
    }
    if(gInput->GetKeyDown(Urho3D::KEY_HOME))
    {
        MoveOn(Direction_Closer, distance);
    }
    if(gInput->GetKeyDown(Urho3D::KEY_PAGEUP))
    {
        MoveOn(Direction_Further, distance);
    }
    if(gInput->GetKeyDown(Urho3D::KEY_END))
    {
        MoveOn(Direction_RotateYAW, -distance);
    }
    if(gInput->GetKeyDown(Urho3D::KEY_PAGEDOWN))
    {
        MoveOn(Direction_RotateYAW, distance);
    }
    if(gInput->GetKeyDown(Urho3D::KEY_INSERT))
    {
        MoveOn(Direction_RotatePITCH, distance);
    }
    if(gInput->GetKeyDown(Urho3D::KEY_DELETE))
    {
        MoveOn(Direction_RotatePITCH, -distance);
    }

    int dX = gInput->GetMouseMoveX();
    int dY = gInput->GetMouseMoveY();

    if((dX || dY) && !gGUI->UnderCursor())
    {
        IntVector2 posCursor = gCursor->GetCursor()->GetPosition();
        posCursor.x_ -= dX;
        posCursor.y_ -= dY;
        if((dY || dX) && gInput->GetMouseButtonDown(Urho3D::MOUSEB_LEFT) && gInput->GetMouseButtonDown(Urho3D::MOUSEB_RIGHT))
        {
            MoveOn(dY < 0 ? Direction_Closer : Direction_Further, fabs(dY / 10.0f));
            gCursor->GetCursor()->SetPosition(posCursor);
        }
        else if((dX || dY) && gInput->GetMouseButtonDown(Urho3D::MOUSEB_RIGHT))
        {
            MoveOn(Direction_RotateYAW, dX / 10.0f);
            MoveOn(Direction_RotatePITCH, dY / 10.0f);
            gCursor->GetCursor()->SetPosition(posCursor);
        }
        else if((dX || dY) && gInput->GetMouseButtonDown(Urho3D::MOUSEB_MIDDLE))
        {
            float k = 3.0f;
            if(dX > 0)
            {
                MoveOn(Direction_Left, dX / k);
            }
            else if(dX < 0)
            {
                MoveOn(Direction_Right, -dX / k);
            }
            if(dY > 0)
            {
                MoveOn(Direction_Forward, dY / k);
            }
            else if(dY < 0)
            {
                MoveOn(Direction_Back, -dY / k);
            }
            gCursor->GetCursor()->SetPosition(posCursor);
        }
    }

    int wheel = gInput->GetMouseMoveWheel();

    if(wheel)
    {
        MoveOn(wheel < 0 ? Direction_Closer : Direction_Further, fabs(wheel * 10.0f));
    }
}

void lCamera::SetPitch(float newPitch)
{
    Quaternion rotation = cameraNode->GetRotation();
    float yaw = rotation.YawAngle();
    float pitch = rotation.PitchAngle();

    float angleNeed = newPitch - pitch;

    Quaternion rotateNeed(-angleNeed, {Sin(yaw + 270.0f), 0.0f, Cos(yaw + 270.0f)});
    cameraNode->RotateAround(lookAt, rotateNeed, Urho3D::TS_WORLD);
}

void lCamera::MoveOn(Direction direction, float distance)
{
    if(!enabled)
    {
        return;
    }

    Quaternion rotation = cameraNode->GetRotation();

    float yaw = rotation.YawAngle();
    float pitch = rotation.PitchAngle();

    if (direction == Direction_RotatePITCH)
    {
        if (pitch > 88.0f && distance > 0.0f)
        {

        }
        else if (pitch < 1.0f && distance < 0.0f)
        {

        }
        else if (pitch + distance < 0.0f)
        {
            SetPitch(0.0f);
        }
        else if (pitch + distance > 89.0f)
        {
            SetPitch(89.0f);
        }
        else
        {
            const float delta = 270.0f;
            Quaternion rotate(-distance, {Sin(yaw + delta), 0.0f, Cos(yaw + delta)});
            cameraNode->RotateAround(lookAt, rotate, Urho3D::TS_WORLD);
        }
    }

    if (direction == Direction_RotateYAW)
    {
        Quaternion rotate(distance, Vector3::UP);
        cameraNode->RotateAround(lookAt, rotate, Urho3D::TS_PARENT);
        LookAt(lookAt);
    }

    if(direction == Direction_Left || direction == Direction_Right)
    {
        yaw += 90.0f;
    }

    float sinYaw = Sin(yaw);
    float cosYaw = Cos(yaw);

    float dX = distance * sinYaw;
    float dZ = distance * cosYaw;

    Vector3 delta = {dX, 0.0f, dZ};

    if(direction == Direction_Forward)
    {
        cameraNode->Translate(delta, Urho3D::TS_WORLD);
        LookAt(lookAt + delta);
    }
    if(direction == Direction_Back)
    {
        cameraNode->Translate(-delta, Urho3D::TS_WORLD);
        LookAt(lookAt - delta);
    }
    if(direction == Direction_Left)
    {
        cameraNode->Translate(-delta, Urho3D::TS_WORLD);
        LookAt(lookAt - delta);
    }
    if(direction == Direction_Right)
    {
        cameraNode->Translate(delta, Urho3D::TS_WORLD);
        LookAt(lookAt + delta);
    }
    if(direction == Direction_Closer)
    {
        Vector3 dist = cameraNode->GetPosition() - lookAt;
        if (dist.Length() > 5.0f)
        {
            cameraNode->Translate(Vector3::FORWARD * distance);
            LookAt(lookAt);
        }
    }
    if(direction == Direction_Further)
    {
        cameraNode->Translate(Vector3::BACK * distance);
        LookAt(lookAt);
    }
}

void lCamera::SetEnabled(bool _enabled)
{
    enabled = _enabled;
}

void lCamera::SetupViewport()
{
    SharedPtr<Viewport> viewport(new Viewport(gContext, gScene, cameraNode->GetComponent<Camera>()));
    gRenderer->SetViewport(0, viewport);
}

SharedPtr<Node> lCamera::GetNode()
{
    return cameraNode;
}