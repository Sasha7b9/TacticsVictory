// 2021/12/16 17:21:45 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    namespace Water
    {
        // Возвращает true, если точка принадлежит водной поверхности
        bool UnderWater(int x, int y);

        void Create();

        float Level();

        // Определяет пересечение с водой
        bool DetectHeight(float x, float y, float *height);
    }
}
