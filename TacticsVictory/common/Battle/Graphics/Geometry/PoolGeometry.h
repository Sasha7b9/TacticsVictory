// 2021/12/15 12:02:22 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    enum class TTypeGeometry
    {
        SelectorLandscape,              // Геометрия выделения ландшафта
        GizmoObject,                    // Gizmo для пристыковки к объекту
        Count
    };

    namespace PoolGeometry
    {
        void Construct();
        void Destruct();

        Node *Get(TTypeGeometry type);
    }
}
