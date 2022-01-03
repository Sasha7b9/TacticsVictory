// 2021/12/17 17:13:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    // Параметры описывают физические свойства юнита
    struct GameObjectParameters
    {
        struct Max
        {
            Vector3D velocity     = Vector3D::ZERO;
            Vector3D speed_rotate = Vector3D::ZERO;
        };

        struct Statistics
        {
            float distance = 0.0f;                  // Пройденная дистанция
        };

        struct Physics
        {
            float    velocity     = 0.0f;
            Point3D  position     = Point3D::ZERO;
            Vector3D direction    = Vector3D::FORWARD;
            Vector3D up           = Vector3D::UP;
            Vector3D up_ortho     = up;                  // Этот вектор нужен для расчёта сбалансированного тангажа.
                                                         // Он не поворачивается при крене
            Vector3D speed_rotate = Vector3D::ZERO;      // y - крен (вдоль оси y), z - рыскание
        };

        Max max;

        int  id            = 0;
        int  number_thread = 0;
        bool exist         = false;     // Если true, то структура существует в сцене, если false - свободна, и может
                                        // быть использована для GameObject

        bool apply_rotate      = true;  // Если true, поворот изменился и нужно его применить
        bool apply_translation = true;  // Если true, изменилась позиция в пространстве, и нужно её применить

        Statistics stat;

        Physics cur;                    // Действующие в текущем кадре параметры
        Physics next;                   // Эти параметры расчитаны в текущем кадре и должны быть применены
                                        // (переписаны в cur и применены к узлам сцены) после окончания расчёта
                                        // всех объектов сцены
    };
}
