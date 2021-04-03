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

    uint sizeZ = TheTerrain->WidthZ();
    uint sizeX = TheTerrain->HeightX();

    camera->SetPosition({ sizeX / 2.0f, 25.0f, static_cast<float>(sizeZ) / 2.0f - 10.0f },
                        { sizeX / 2.0f, 0.0f, (sizeZ / 2.0f) });

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


void CameraT::PostUpdate(float time)
{
    if(!enabled || TheConsole->IsActive())
    {
        return;
    }

    CursorT::Type::E cursor = TheCursor->GetType();

    const float MOVE_SPEED = 30.0f;

    float distance = MOVE_SPEED * time;

    if(CURSOR_UP || CURSOR_TOP_LEFT || CURSOR_TOP_RIGHT || ((PRESS_UP || PRESS_W) && arrowEnabled))
    {
        MoveOn(Direction::Forward, distance);
    }
    if(CURSOR_DOWN || CURSOR_DOWN_LEFT || CURSOR_DOWN_RIGhT || ((PRESS_DOWN || PRESS_S) && arrowEnabled))
    {
        MoveOn(Direction::Back, distance);
    }
    if(CURSOR_LEFT || CURSOR_TOP_LEFT || CURSOR_DOWN_LEFT || ((PRESS_LEFT || PRESS_A) && arrowEnabled))
    {
        MoveOn(Direction::Left, distance);
    }
    if(CURSOR_RIGHT || CURSOR_TOP_RIGHT || CURSOR_DOWN_RIGhT || ((PRESS_RIGHT || PRESS_D) && arrowEnabled))
    {
        MoveOn(Direction::Right, distance);
    }
    if(PRESS_HOME || PRESS_Q)
    {
        MoveOn(Direction::Closer, distance);
    }
    if(PRESS_PAGEUP || PRESS_E)
    {
        MoveOn(Direction::Further, distance);
    }
    if(TheInput->GetKeyDown(KEY_END))
    {
        MoveOn(Direction::RotateYAW, -distance);
    }
    if(TheInput->GetKeyDown(KEY_PAGEDOWN))
    {
        MoveOn(Direction::RotateYAW, distance);
    }
    if(TheInput->GetKeyDown(KEY_INSERT))
    {
        MoveOn(Direction::RotatePITCH, distance);
    }
    if(TheInput->GetKeyDown(KEY_DELETE))
    {
        MoveOn(Direction::RotatePITCH, -distance);
    }

    int dX = TheInput->GetMouseMoveX();
    int dY = TheInput->GetMouseMoveY();

    if((dX || dY) && !TheGUI->UnderCursor())
    {
        IntVector2 posCursor = TheCursor->GetCursor()->GetPosition();
        posCursor.x_ -= dX;
        posCursor.y_ -= dY;
        if((dY || dX) && TheInput->GetMouseButtonDown(MOUSEB_LEFT) && TheInput->GetMouseButtonDown(MOUSEB_RIGHT))
        {
            MoveOn(dY < 0 ? Direction::Closer : Direction::Further, fabs(dY / 10.0f));
            TheCursor->GetCursor()->SetPosition(posCursor);
        }
        else if((dX || dY) && TheInput->GetMouseButtonDown(MOUSEB_RIGHT))
        {
            MoveOn(Direction::RotateYAW, dX / 10.0f);
            MoveOn(Direction::RotatePITCH, dY / 10.0f);
            TheCursor->GetCursor()->SetPosition(posCursor);
        }
        else if((dX || dY) && TheInput->GetMouseButtonDown(MOUSEB_MIDDLE))
        {
            float k = 20.0f;
            if(dX > 0)
            {
                MoveOn(Direction::Left, dX / k);
            }
            else if(dX < 0)
            {
                MoveOn(Direction::Right, -dX / k);
            }
            if(dY > 0)
            {
                MoveOn(Direction::Forward, dY / k);
            }
            else if(dY < 0)
            {
                MoveOn(Direction::Back, -dY / k);
            }
            TheCursor->GetCursor()->SetPosition(posCursor);
        }
    }

    int wheel = TheInput->GetMouseMoveWheel();

    if(wheel != 0)
    {
        MoveOn(wheel < 0 ? Direction::Closer : Direction::Further, fabs(wheel * 10.0f));
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
    Camera *camera = cameraNode->GetComponent<Camera>();

    SharedPtr<Viewport> viewport(new Viewport(TheContext, TheScene, camera));

    TheRenderer->SetViewport(0, viewport);
}


SharedPtr<Node> CameraT::GetNode()
{
    return cameraNode;
}


Ray CameraT::GetCursorRay()
{
    IntVector2 pos = TheUI->GetCursorPosition();
    return cameraNode->GetComponent<Camera>()->GetScreenRay(static_cast<float>(pos.x_) / TheGraphics->GetWidth(), static_cast<float>(pos.y_) / TheGraphics->GetHeight());
}
