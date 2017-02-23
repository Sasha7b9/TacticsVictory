#include <stdafx.h>
#include "Camera.h"
#include "GUI/Elements/Cursor.h"
#include "GUI/GUI.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CURSOR_UP           (cursor == TypeCursor_Up)
#define CURSOR_DOWN         (cursor == TypeCursor_Down)
#define CURSOR_LEFT         (cursor == TypeCursor_Left)
#define CURSOR_RIGHT        (cursor == TypeCursor_Right)
#define CURSOR_TOP_LEFT     (cursor == TypeCursor_TopLeft)
#define CURSOR_TOP_RIGHT    (cursor == TypeCursor_TopRight)
#define CURSOR_DOWN_LEFT    (cursor == TypeCursor_DownLeft)
#define CURSOR_DOWN_RIGhT   (cursor == TypeCursor_DownRight)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CameraRTS::CameraRTS()
{
    cameraNode = gScene->CreateChild("Camera");

    Camera *camera = cameraNode->CreateComponent<Camera>();
    camera->SetFarClip(1000.0f);
    camera->SetNearClip(1.0f);
    cameraNode->SetRotation(Quaternion(pitch, yaw, 0.0f));
    cameraNode->SetPosition({-37.0f, 45.0f, 15.0f});

    light = cameraNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_POINT);
    light->SetRange(25.0f);
    light->SetEnabled(true);

    SetupViewport();

    Node *listenerNode = cameraNode->CreateChild("Listener");
    SoundListener *listener = listenerNode->CreateComponent<SoundListener>();
    gAudio->SetListener(listener);
}

Vector3 CameraRTS::GetPosition()
{
    return cameraNode->GetPosition();
}

void CameraRTS::SetPosition(const Vector3 &position)
{
    cameraNode->SetPosition(position);
}

void CameraRTS::SetPosition(const Vector3& position, const Vector3& lookAt_)
{
    cameraNode->SetPosition(position);
    lookAt = lookAt_;
    cameraNode->LookAt(lookAt);
}

void CameraRTS::LookAt(const Vector3 &lookAt_)
{
    lookAt = lookAt_;
    cameraNode->LookAt(lookAt);
}

void CameraRTS::ParallelTranslateLookAt(const Vector3 &lookAt_)
{
    Vector3 delta = lookAt_ - lookAt;
    lookAt = lookAt_;
    cameraNode->SetPosition(cameraNode->GetPosition() + delta);
    cameraNode->LookAt(lookAt);
}

void CameraRTS::Move(float time)
{
    if(!enabled)
    {
        return;
    }

    const float MOVE_SPEED = 30.0f;

    float distance = MOVE_SPEED * time;

    TypeCursor cursor = gCursor->GetType();

    if(CURSOR_UP || CURSOR_TOP_LEFT || CURSOR_TOP_RIGHT || ((PRESS_KEY_UP || PRESS_KEY_W) && arrowEnabled))
    {
        MoveOn(Direction_Forward, distance);
    }
    if(CURSOR_DOWN || CURSOR_DOWN_LEFT || CURSOR_DOWN_RIGhT || ((PRESS_KEY_DOWN || PRESS_KEY_S) && arrowEnabled))
    {
        MoveOn(Direction_Back, distance);
    }
    if(CURSOR_LEFT || CURSOR_TOP_LEFT || CURSOR_DOWN_LEFT || ((PRESS_KEY_LEFT || PRESS_KEY_A) && arrowEnabled))
    {
        MoveOn(Direction_Left, distance);
    }
    if(CURSOR_RIGHT || CURSOR_TOP_RIGHT || CURSOR_DOWN_RIGhT || ((PRESS_KEY_RIGHT || PRESS_KEY_D) && arrowEnabled))
    {
        MoveOn(Direction_Right, distance);
    }
    if(gInput->GetKeyDown(KEY_HOME))
    {
        MoveOn(Direction_Closer, distance);
    }
    if(gInput->GetKeyDown(KEY_PAGEUP))
    {
        MoveOn(Direction_Further, distance);
    }
    if(gInput->GetKeyDown(KEY_END))
    {
        MoveOn(Direction_RotateYAW, -distance);
    }
    if(gInput->GetKeyDown(KEY_PAGEDOWN))
    {
        MoveOn(Direction_RotateYAW, distance);
    }
    if(gInput->GetKeyDown(KEY_INSERT))
    {
        MoveOn(Direction_RotatePITCH, distance);
    }
    if(gInput->GetKeyDown(KEY_DELETE))
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
        if((dY || dX) && gInput->GetMouseButtonDown(MOUSEB_LEFT) && gInput->GetMouseButtonDown(MOUSEB_RIGHT))
        {
            MoveOn(dY < 0 ? Direction_Closer : Direction_Further, fabs(dY / 10.0f));
            gCursor->GetCursor()->SetPosition(posCursor);
        }
        else if((dX || dY) && gInput->GetMouseButtonDown(MOUSEB_RIGHT))
        {
            MoveOn(Direction_RotateYAW, dX / 10.0f);
            MoveOn(Direction_RotatePITCH, dY / 10.0f);
            gCursor->GetCursor()->SetPosition(posCursor);
        }
        else if((dX || dY) && gInput->GetMouseButtonDown(MOUSEB_MIDDLE))
        {
            float k = 20.0f;
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

void CameraRTS::SetPitch(float newPitch)
{
    Quaternion rotation = cameraNode->GetRotation();
    float yawAngle = rotation.YawAngle();
    float angleNeed = newPitch - rotation.PitchAngle();

    Quaternion rotateNeed(-angleNeed, {Sin(yawAngle + 270.0f), 0.0f, Cos(yawAngle + 270.0f)});
    cameraNode->RotateAround(lookAt, rotateNeed, TS_WORLD);
}

void CameraRTS::MoveOn(Direction direction, float distance)
{
    if(!enabled)
    {
        return;
    }

    Quaternion rotation = cameraNode->GetRotation();

    float yawAngle = rotation.YawAngle();
    float pitchAngle = rotation.PitchAngle();

    if (direction == Direction_RotatePITCH)
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

    if (direction == Direction_RotateYAW)
    {
        Quaternion rotate(distance, Vector3::UP);
        cameraNode->RotateAround(lookAt, rotate, TS_PARENT);
        LookAt(lookAt);
    }

    if(direction == Direction_Left || direction == Direction_Right)
    {
        yawAngle += 90.0f;
    }

    float sinYaw = Sin(yawAngle);
    float cosYaw = Cos(yawAngle);

    float dX = distance * sinYaw;
    float dZ = distance * cosYaw;

    Vector3 delta = {dX, 0.0f, dZ};

    if(direction == Direction_Forward)
    {
        cameraNode->Translate(delta, TS_WORLD);
        LookAt(lookAt + delta);
    }
    if(direction == Direction_Back)
    {
        cameraNode->Translate(-delta, TS_WORLD);
        LookAt(lookAt - delta);
    }
    if(direction == Direction_Left)
    {
        cameraNode->Translate(-delta, TS_WORLD);
        LookAt(lookAt - delta);
    }
    if(direction == Direction_Right)
    {
        cameraNode->Translate(delta, TS_WORLD);
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

void CameraRTS::SetEnabled(bool _enabled)
{
    enabled = _enabled;
}

void CameraRTS::SetupViewport()
{
    SharedPtr<Viewport> viewport(new Viewport(gContext, gScene, cameraNode->GetComponent<Camera>()));
    gRenderer->SetViewport(0, viewport);
}

SharedPtr<Node> CameraRTS::GetNode()
{
    return cameraNode;
}

Ray CameraRTS::GetCursorRay()
{
    IntVector2 pos = gUI->GetCursorPosition();
    return cameraNode->GetComponent<Camera>()->GetScreenRay((float)pos.x_ / gGraphics->GetWidth(), (float)pos.y_ / gGraphics->GetHeight());
}
