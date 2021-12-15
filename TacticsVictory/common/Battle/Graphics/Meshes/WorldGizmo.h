// 2021/12/3 13:54:01 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    class WorldGizmo : public Node
    {
    public:

        WorldGizmo(float size = 1500.0f, float radius = 0.05f);

    private:

        Node *CreateAxis(const ColorRGBA &color, const Transform4D &transform, const Point3D &position);
        float size = 0.0f;
        float radius = 0.05f;
    };

}
