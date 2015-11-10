#pragma once


#include "Graphics/Objects/Plane.h"
#include "Game/Objects/Terrain.h"
#include "Graphics/Objects/Line.h"


class Editor : public Object
{
    URHO3D_OBJECT(Editor, Object);
public:
    Editor(Context *context);
    void Run();
    void ClearScene();

private:
    Plane currentPlane;
    Plane selectedPlane;

    Line currentEdge;
    Line selectedEdge;

    SharedPtr<Node> lightNode;

    void HandlePostRenderUpdate(StringHash, VariantMap&);
    void HandleMouseDown(StringHash, VariantMap&);
    void HandleKeyDown(StringHash, VariantMap&);

    Editor& operator=(const Editor&)
    {};
};