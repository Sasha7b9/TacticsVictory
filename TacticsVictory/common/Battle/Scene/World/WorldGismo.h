// 2021/12/3 13:54:01 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    class WorldGizmo : public Node
    {
    public:
        WorldGizmo();
    private:
        Node *CreateAxis(const ColorRGBA &color, const Transform4D &transform, const Point3D &position);
    };

}
