/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "Scene/Primitives/_PlaneTV.h"


class Editor : public Object
{
    URHO3D_OBJECT(Editor, Object);
public:
    Editor(Context *context);
    void Run();
    void ClearScene();

private:
    PlaneTV currentPlane;
    PlaneTV selectedPlane;
    Line currentEdge;
    Line selectedEdge;
    SharedPtr<Node> lightNode;

    void HandlePostRenderUpdate(StringHash, VariantMap&);
    void HandleMouseDown(StringHash, VariantMap&);
    void HandleKeyDown(StringHash, VariantMap&);
};
