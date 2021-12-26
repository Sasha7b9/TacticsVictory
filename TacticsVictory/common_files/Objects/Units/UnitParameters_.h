// 2021/12/17 17:13:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    // Параметры описывают физические свойства юнита
    struct UnitParameters
    {
        struct Max
        {
            Vector3D speed  = Vector3D::ZERO;
            Vector3D rotate = Vector3D::ZERO;
            float accelerateSpeed = 0.0f;
        };

        Max max;

        float speed           = 0.0f;
        Vector3D direction    = Vector3D::FORWARD;
        Vector3D up           = Vector3D::UP;
    };
}
