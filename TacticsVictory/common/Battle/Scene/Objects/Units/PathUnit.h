// 2021/12/3 20:53:21 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    // Класс визуализирует путь перемещения юнита
    class PathUnit : public Node
    {
    public:
        static void Create();

        static void PowerOn();

        static void PowerOff();

        static void SetPosition(const Point3D &position);

    private:
        PathUnit(float x, float y);

        Node *CreateMember(float x, float y);
    };
}
