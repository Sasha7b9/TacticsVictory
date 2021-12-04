// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include <stdafx.h>
#include "CameraRTS.h"
#include "GUI/Widgets/CursorGUI.h"
#include "Utils/Math.h"
#include "Input/Mouse.h"
#include "Scene/World/GameWorld.h"


using namespace Pi;


CameraRTS::CameraRTS()
    : FrustumCamera(2.0f, 1.0f)
{
    FrustumCameraObject *object = GetObject();
    object->SetFrustumFlags(PiFlagFrustum::Infinite);
    object->SetFarDepth(1e7);
    SetObject(object);
    Update();
}

CameraRTS::~CameraRTS()
{}

void CameraRTS::Preprocess()
{
    FrustumCamera::Preprocess();
}

void CameraRTS::ZoomIn()
{
    SetDistance(distance * 0.95f);
}

void CameraRTS::ZoomOut()
{
    SetDistance(distance * 1.05f);
}

void CameraRTS::TiltAngleIncrease()
{
    SetTiltAngle(angleTilt + STEP_TILT_ANGLE);
}

void CameraRTS::TiltAngleDecrease()
{
    SetTiltAngle(angleTilt - STEP_TILT_ANGLE);
}

void CameraRTS::Move()
{
    float dt = TheTimeMgr->GetFloatDeltaTime() * 0.005f;
    float deltaFwd = 0.0f;                  // Смещение по линии вперёд/назад
    float deltaRight = 0.0f;                // Смещение по линии влево/вправо

    const float sensitivity = 300.0f;

    float deltaX = -sensitivity * TheInputMgr->GetMouseDeltaX();
    float deltaY = -sensitivity * TheInputMgr->GetMouseDeltaY();

    speed.x += deltaX / 20.0f;
    speed.y += deltaY / 20.0f;

    GameWorld *world = GameWorld::Get();

    if(TheMouse->RightIsPressed())
    {
        if(TheMouse->LeftIsPressed())
        {
            distance += (deltaY * dt * distance / 10.0f);
        }
        else
        {
            azimuth -= deltaX * dt / 10.0f;
            angleTilt -= deltaY * dt / 10.0f;
        }
    }
    else if (TheMouse->MiddleIsPressed())
    {
        deltaFwd -= deltaY * dt / 5.0f;
        deltaRight += deltaX * dt / 5.0f;
    }
    else if(deltaX != 0.0f || deltaY != 0.0f)  
    {
        world->ChangeCursorPosition(deltaX, deltaY);
    }

    Point2D cursorPos = TheCursor->position;

    float autoScrollThreshold = 0.005f;

    float displayWidth = (float)TheDisplayMgr->GetDisplayWidth();
    float displayHeight = (float)TheDisplayMgr->GetDisplayHeight();

    if((cursorPos.x > autoScrollThreshold * displayWidth) && (cursorPos.x < (1.0f - autoScrollThreshold) * displayWidth))
    {
        speed.x = 0.0f;
    }

    deltaRight += speed.x * dt;

    if((cursorPos.y > autoScrollThreshold * displayHeight) && (cursorPos.y < (1.0f - autoScrollThreshold) * displayHeight))
    {
        speed.y = 0.0f;
    }

    deltaFwd -= speed.y * dt;

    if((movementFlags & (uint)E::MovekForward))
    {
        deltaFwd += 1.0f * dt;
    }
    if((movementFlags & (uint)E::MoveBackward))
    {
        deltaFwd -= 1.0f * dt;
    }
    if((movementFlags & (uint)E::MoveRight))
    {
        deltaRight += 1.0f * dt;
    }
    if((movementFlags & (uint)E::MoveLeft))
    {
        deltaRight -= 1.0f * dt;
    }
    if((movementFlags & (uint)E::RotateLeft))
    {
        azimuth -= 1.0f * dt / 3;
    }
    if((movementFlags & (uint)E::RotateRight))
    {
        azimuth += 1.0f * dt / 3;
    }
    if((movementFlags & (uint)E::RotateTop))
    {
        angleTilt -= 1.0f * dt / 3;
    }
    if((movementFlags & (uint)E::RotateDown))
    {
        angleTilt += 1.0f * dt / 3;
    }
    if((movementFlags & (uint)E::ZoomIn))
    {
        distance += 5.0f * dt;
    }
    if((movementFlags & (uint)E::ZoomOut))
    {
        distance -= 5.0f * dt;
    }
    if (movementFlags & (uint)E::MoveCenter)
    {
        pointFocus = Point3D::ZERO;
        if (distance > 50.0f)
        {
            distance = 50.0f;
        }
    }

    distance = Mathem::LimitationFloat(distance, MIN_DISTANCE, MAX_DISTANCE);
    angleTilt = Mathem::LimitationFloat(angleTilt, MIN_TILT_ANGLE, MAX_TILT_ANGLE);

    Vector3D vecMoveXY = GetVectorMoveXY(deltaRight, deltaFwd, azimuth); //-V764
    pointFocus += vecMoveXY;

    Point3D camPosition(0.0f, -distance, 0.0f);

    Transform4D rotateTransform;
    rotateTransform.SetRotationAboutX(angleTilt);

    Matrix3D orbitMatrix;
    orbitMatrix.SetRotationAboutZ(azimuth);

    rotateTransform = orbitMatrix * rotateTransform;

    camPosition = rotateTransform * camPosition;
    camPosition += pointFocus;

    SetNodePosition(camPosition);
    LookAtPoint(pointFocus);
}

void CameraRTS::MoveOn(const Vector3D &shift)
{
    SetNodePosition(GetNodePosition() + shift);
    pointFocus += shift;
    LookAtPoint(pointFocus);
}

void CameraRTS::SetTiltAngle(float tiltAngle)
{
    angleTilt = Mathem::LimitationFloat(tiltAngle, MIN_TILT_ANGLE, MAX_TILT_ANGLE);
}

void CameraRTS::SetDistance(float _distance)
{
    distance = Mathem::LimitationFloat(_distance, MIN_DISTANCE, MAX_DISTANCE);
}

Vector3D CameraRTS::GetVectorMoveXY(float deltaFwd, float deltaRight, float anglePlaneXY)
{
    Vector3D vectorXY(deltaFwd, deltaRight, 0.0f);
    Matrix3D matRotateXY;
    matRotateXY.SetRotationAboutZ(-anglePlaneXY);
    Vector3D vectorMove = vectorXY * matRotateXY;
    return vectorMove;
}

Ray CameraRTS::GetWorldRayFromPoint(const Point2D& p)
{
    const Rect &viewRect = GetObject()->GetViewRect();
    float x = static_cast<float>(p.x) / (float)viewRect.Width();
    float y = static_cast<float>(p.y) / (float)viewRect.Height();

    Ray ray;

    CastRay(x, y, &ray);

    const Transform4D &cameraTransform = GetNodeTransform();
    ray.origin = cameraTransform * ray.origin;
    ray.direction = (cameraTransform * ray.direction).Normalize();

    ray.radius = 0.0f;
    ray.tmin = 0.0f;
    ray.tmax = 500.0f;

    return ray;
}

bool CameraRTS::GetIntersectionPlaneZ(const Point2D& p, Point3D *point)
{
    Ray ray = GetWorldRayFromPoint(p);

    Vector3D a(1.0f, 0.0f, 0.0f);
    Vector3D b(0.0f, 0.0f, 0.0f);
    Vector3D c(0.0f, 1.0f, 0.0f);

    Vector3D n = Cross(b - a, c - a);

    Point3D x = ray.origin;
    Point3D y = x + ray.direction;

    Vector3D v = a - x;

    Vector3D w = y - x;

    float d = Dot(n, v);
    float e = Dot(n, w);

    if(e != 0) 
    {
        *point = x + w * d / e;
        return true;
    }

    *point = Point3D(0, 0, 0);
    return false;
}