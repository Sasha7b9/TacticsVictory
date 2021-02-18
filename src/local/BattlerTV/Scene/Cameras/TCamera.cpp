/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include "stdafx.h"
#include "GUI/TCursor.h"
#include "GUI/TGUI.h"


#define CURSOR_UP           (cursor == TypeCursor_Up)
#define CURSOR_DOWN         (cursor == TypeCursor_Down)
#define CURSOR_LEFT         (cursor == TypeCursor_Left)
#define CURSOR_RIGHT        (cursor == TypeCursor_Right)
#define CURSOR_TOP_LEFT     (cursor == TypeCursor_TopLeft)
#define CURSOR_TOP_RIGHT    (cursor == TypeCursor_TopRight)
#define CURSOR_DOWN_LEFT    (cursor == TypeCursor_DownLeft)
#define CURSOR_DOWN_RIGhT   (cursor == TypeCursor_DownRight)


TCamera::TCamera(Scene *scene)
{
    cameraNode = scene->CreateChild("Camera");

    Camera *camera = cameraNode->CreateComponent<Camera>();
    camera->SetFarClip(1000.0f);
    camera->SetNearClip(1.0f);
    cameraNode->SetRotation(Quaternion(pitch, yaw, 0.0f));
    cameraNode->SetPosition({120.0f, 50.0f, -160.0f});

    light = cameraNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_POINT);
    light->SetRange(25.0f);
    light->SetEnabled(true);

    SetupViewport();
    Node *listenerNode = cameraNode->CreateChild("Listener");
    SoundListener *listener = listenerNode->CreateComponent<SoundListener>();
    TheAudio->SetListener(listener);
}


TCamera *TCamera::Create(Scene *scene)
{
    TCamera *camera = new TCamera(scene);

    uint sizeX = TheScene->level[0].Size();
    uint sizeZ = TheScene->level.Size();

    camera->SetPosition({ sizeX / 2.0f, 25.0f, -static_cast<float>(sizeZ) / 2.0f - 10.0f },
                        { sizeX / 2.0f, 0.0f, -(sizeZ / 2.0f) });

    return camera;
}


Vector3 TCamera::GetPosition()
{
    return cameraNode->GetPosition();
}


void TCamera::SetPosition(const Vector3 &position)
{
    cameraNode->SetPosition(position);
}


void TCamera::SetPosition(const Vector3& position, const Vector3& lookAt_)
{
    cameraNode->SetPosition(position);
    lookAt = lookAt_;
    cameraNode->LookAt(lookAt);
}

void TCamera::LookAt(const Vector3 &lookAt_)
{
    lookAt = lookAt_;
    cameraNode->LookAt(lookAt);
}


void TCamera::ParallelTranslateLookAt(const Vector3 &lookAt_)
{
    Vector3 delta = lookAt_ - lookAt;
    lookAt = lookAt_;
    cameraNode->SetPosition(cameraNode->GetPosition() + delta);
    cameraNode->LookAt(lookAt);
}


void TCamera::Move(float time) //-V2008
{
    if(!enabled || TheConsole->IsActive())
    {
        return;
    }

    const float MOVE_SPEED = 30.0f;

    float distance = MOVE_SPEED * time;

    TypeCursor cursor = TheCursor->GetType();

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

    if(wheel)
    {
        MoveOn(wheel < 0 ? Direction::Closer : Direction::Further, fabs(wheel * 10.0f));
    }
}


void TCamera::SetPitch(float newPitch)
{
    Quaternion rotation = cameraNode->GetRotation();
    float yawAngle = rotation.YawAngle();
    float angleNeed = newPitch - rotation.PitchAngle();

    Quaternion rotateNeed(-angleNeed, {Sin(yawAngle + 270.0f), 0.0f, Cos(yawAngle + 270.0f)});
    cameraNode->RotateAround(lookAt, rotateNeed, TS_WORLD);
}


void TCamera::MoveOn(Direction::E direction, float distance)
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


void TCamera::SetEnabled(bool _enabled)
{
    enabled = _enabled;
}


void TCamera::SetupViewport()
{
    Camera *camera = cameraNode->GetComponent<Camera>();

    SharedPtr<Viewport> viewport(new Viewport(TheContext, TheScene->scene, camera));

    TheRenderer->SetViewport(0, viewport);
}


SharedPtr<Node> TCamera::GetNode()
{
    return cameraNode;
}


Ray TCamera::GetCursorRay()
{
    IntVector2 pos = TheUI->GetCursorPosition();
    return cameraNode->GetComponent<Camera>()->GetScreenRay(static_cast<float>(pos.x_) / TheGraphics->GetWidth(), static_cast<float>(pos.y_) / TheGraphics->GetHeight());
}
