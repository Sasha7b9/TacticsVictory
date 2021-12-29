// 2021/12/17 17:13:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    // Параметры описывают физические свойства юнита
    struct UnitParameters
    {
        struct Max
        {
            Vector3D speed           = Vector3D::ZERO;
            Vector3D rotate          = Vector3D::ZERO;
            float    accelerateSpeed = 0.0f;
        };

        struct Statistics
        {
            float distance = 0.0f;              // Пройденная дистанция
        };

        Max max;

        float    speed        = 0.0f;
        Vector3D direction    = Vector3D::FORWARD;
        Vector3D up           = Vector3D::UP;
        Vector3D upPitch      = up;                 // Этот вектор нужен для расчёта сбалансированного тангажа.
                                                    // Он не поворачивается при крене
        Vector3D speedRotate  = Vector3D::ZERO;     // y - крен (вдоль оси y), z - рыскание
        Point3D  position     = Point3D::ZERO;

        Statistics stat;

        bool applyRotate      = true;               // Если true, поворот изменился и нужно его применить
        bool applyTranslation = true;               // Если true, изменилась позиция в пространстве, и нужно её применить
    };
}
