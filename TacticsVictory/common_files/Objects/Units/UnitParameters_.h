// 2021/12/17 17:13:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    // Параметры описывают физические свойства юнита
    struct UnitParameters
    {
        UnitParameters *Replicate() const
        {
            UnitParameters *parameters = new UnitParameters();
            *parameters = *this;
            return parameters;
        }

        struct Max
        {
            Vector3D speed  = Vector3D::ZERO;
            Vector3D rotate = Vector3D::ZERO;
        };

        Max max;

        Vector3D speed     = Vector3D::ZERO;
        Vector3D direction = Vector3D::ZERO;
    };
}
