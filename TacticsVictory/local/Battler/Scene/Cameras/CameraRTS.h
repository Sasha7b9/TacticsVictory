﻿// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    class CameraRTS : public FrustumCamera, public Singleton<CameraRTS>
    {
    
    public:
    
        enum class E
        {
            MovekForward = 1 << 0,
            MoveBackward = 1 << 1,
            MoveLeft = 1 << 2,
            MoveRight = 1 << 3,
            MoveCenter = 1 << 4,
            RotateLeft = 1 << 5,
            RotateRight = 1 << 6,
            RotateTop = 1 << 7,
            RotateDown = 1 << 8,
            ZoomIn = 1 << 9,
            ZoomOut = 1 << 10
        };
    
    public:
        CameraRTS();
        ~CameraRTS();

        static CameraRTS *self;
    
        virtual void Preprocess() override;
        virtual void Move() override;
    
        void AddNavFlag(CameraRTS::E flag)
        {
            movementFlags |= (uint)flag;
        }
    
        void RemoveNavFlag(CameraRTS::E flag)
        {
            movementFlags &= ~(uint)flag;
        }
    
        Ray GetWorldRayFromPoint(const Point2D& p);
        bool GetIntersectionPlaneZ(const Point2D& p, Point3D *point);
    
        Point3D GetCurrentFocus() const
        {
            return pointFocus;
        }
    
        void MoveOn(const Vector3D &shift);
    
        void ZoomIn();
        void ZoomOut();
        void TiltAngleIncrease();
        void TiltAngleDecrease();

        Vector2D GetSpeed() const { return speed; }
    
    private:
        ulong movementFlags = 0;
        Point3D pointFocus {10.0f, 25.0f, 0.0f};     // Точка, вокруг которой происходит вращение камера. Сюда всегда направлен её взгляд
        float distance = 25.0f;
    
        float azimuth = -0.5f * K::pi;              // Угол поворота в горизонтальной плоскости
        float angleTilt = -0.1f * K::pi;            // Угол поворота в вертикальной плоскости

        Vector2D speed {0.0f, 0.0f};                // Скорость камеры в плоскости ландашфта
    
        Vector3D GetVectorMoveXY(float deltaFwd, float deltaRight, float anglePlaneXY);
        void SetDistance(float distance);
        void SetTiltAngle(float tiltAngle);
    
        const float MIN_DISTANCE = 2.0F;
        const float MAX_DISTANCE = 2.5e2F;
        const float MIN_TILT_ANGLE = -0.499F * K::pi;
        const float MAX_TILT_ANGLE = -0.00001F * K::pi;
        const float STEP_TILT_ANGLE = 0.05F;
    };
}
