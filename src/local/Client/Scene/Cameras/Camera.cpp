// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/GUI.h"
#include "Scene/SceneC.h"
#include "Scene/Cameras/Camera.h"


#define CURSOR_UP           (cursor == CursorT::Type::Up)
#define CURSOR_DOWN         (cursor == CursorT::Type::Down)
#define CURSOR_LEFT         (cursor == CursorT::Type::Left)
#define CURSOR_RIGHT        (cursor == CursorT::Type::Right)
#define CURSOR_TOP_LEFT     (cursor == CursorT::Type::TopLeft)
#define CURSOR_TOP_RIGHT    (cursor == CursorT::Type::TopRight)
#define CURSOR_DOWN_LEFT    (cursor == CursorT::Type::DownLeft)
#define CURSOR_DOWN_RIGhT   (cursor == CursorT::Type::DownRight)


CameraT::CameraT(Context *context) : LogicComponent(context)
{
    cameraNode = TheScene->CreateChild("Camera");

    Camera *camera = cameraNode->CreateComponent<Camera>(LOCAL);
    camera->SetFarClip(1000.0f);
    camera->SetNearClip(1.0f);
    cameraNode->SetRotation(Quaternion(pitch, yaw, 0.0f));
    cameraNode->SetPosition({120.0f, 50.0f, -160.0f});

    light = cameraNode->CreateComponent<Light>(LOCAL);
    light->SetLightType(LIGHT_POINT);
    light->SetRange(25.0f);
    light->SetEnabled(true);

    SetupViewport();
    Node *listenerNode = cameraNode->CreateChild("Listener");
    SoundListener *listener = listenerNode->CreateComponent<SoundListener>(LOCAL);
    TheAudio->SetListener(listener);
}


void CameraT::RegisterObject()
{
    TheContext->RegisterFactory<CameraT>();
}


SharedPtr<CameraT> CameraT::Create()
{
    SharedPtr<CameraT> camera(TheScene->CreateChild("TCamera")->CreateComponent<CameraT>(LOCAL));

    return camera;
}


Vector3 CameraT::GetPosition()
{
    return cameraNode ? cameraNode->GetPosition() : Vector3::ZERO;
}


void CameraT::SetPosition(const Vector3 &position)
{
    cameraNode->SetPosition(position);
}


void CameraT::SetPosition(const Vector3& position, const Vector3& lookAt_)
{
    cameraNode->SetPosition(position);
    lookAt = lookAt_;
    cameraNode->LookAt(lookAt);
}

void CameraT::LookAt(const Vector3 &lookAt_)
{
    lookAt = lookAt_;
    cameraNode->LookAt(lookAt);
}


void CameraT::ParallelTranslateLookAt(const Vector3 &lookAt_)
{
    Vector3 delta = lookAt_ - lookAt;
    lookAt = lookAt_;
    cameraNode->SetPosition(cameraNode->GetPosition() + delta);
    cameraNode->LookAt(lookAt);
}


void CameraT::PostUpdate(float /*time*/)
{
    if(!enabled || TheConsole->IsActive())
    {
        return;
    }
}


void CameraT::SetPitch(float newPitch)
{
    Quaternion rotation = cameraNode->GetRotation();
    float yawAngle = rotation.YawAngle();
    float angleNeed = newPitch - rotation.PitchAngle();

    Quaternion rotateNeed(-angleNeed, {Sin(yawAngle + 270.0f), 0.0f, Cos(yawAngle + 270.0f)});
    cameraNode->RotateAround(lookAt, rotateNeed, TS_WORLD);
}


void CameraT::MoveOn(Direction::E direction, float distance)
{
    if(!enabled)
    {
        return;
    }

    Quaternion rotation = cameraNode->GetRotation();

    float yawAngle = rotation.YawAngle();
    float pitchAngle = rotation.PitchAngle();

    if (direction == Direction::RotatePITCH)
    {
        if (pitchAngle > 88.0f && distance > 0.0f)
        {

        }
        else if (pitchAngle < 1.0f && distance < 0.0f)
        {

        }
        else if (pitchAngle + distance < 0.0f)
        {
            SetPitch(0.0f);
        }
        else if (pitchAngle + distance > 89.0f)
        {
            SetPitch(89.0f);
        }
        else
        {
            const float delta = 270.0f;
            Quaternion rotate(-distance, {Sin(yawAngle + delta), 0.0f, Cos(yawAngle + delta)});
            cameraNode->RotateAround(lookAt, rotate, TS_WORLD);
        }
    }

    if (direction == Direction::RotateYAW)
    {
        Quaternion rotate(distance, Vector3::UP);
        cameraNode->RotateAround(lookAt, rotate, TS_PARENT);
        LookAt(lookAt);
    }

    if(direction == Direction::Left || direction == Direction::Right)
    {
        yawAngle += 90.0f;
    }

    float sinYaw = Sin(yawAngle);
    float cosYaw = Cos(yawAngle);

    float dX = distance * sinYaw;
    float dZ = distance * cosYaw;

    Vector3 delta = {dX, 0.0f, dZ};

    if(direction == Direction::Forward)
    {
        cameraNode->Translate(delta, TS_WORLD);
        LookAt(lookAt + delta);
    }
    if(direction == Direction::Back)
    {
        cameraNode->Translate(-delta, TS_WORLD);
        LookAt(lookAt - delta);
    }
    if(direction == Direction::Left)
    {
        cameraNode->Translate(-delta, TS_WORLD);
        LookAt(lookAt - delta);
    }
    if(direction == Direction::Right)
    {
        cameraNode->Translate(delta, TS_WORLD);
        LookAt(lookAt + delta);
    }
    if(direction == Direction::Closer)
    {
        Vector3 dist = cameraNode->GetPosition() - lookAt;
        if (dist.Length() > 5.0f)
        {
            cameraNode->Translate(Vector3::FORWARD * distance);
            LookAt(lookAt);
        }
    }
    if(direction == Direction::Further)
    {
        cameraNode->Translate(Vector3::BACK * distance);
        LookAt(lookAt);
    }
}


void CameraT::SetEnabled(bool _enabled)
{
    enabled = _enabled;
}


void CameraT::SetupViewport()
{
}


SharedPtr<Node> CameraT::GetNode()
{
    return cameraNode;
}


Ray CameraT::GetCursorRay()
{
}
