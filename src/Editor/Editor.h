#pragma once


#include "Graphics/Objects/Plane.h"
#include "Game/Objects/Terrain.h"
#include "Graphics/Objects/Line.h"


class lEditor : public Object
{
    OBJECT(lEditor);
public:
    lEditor(Context *context);
    void Run();
    void ClearScene();

private:
    lPlane currentPlane;
    lPlane selectedPlane;

    lLine currentEdge;
    lLine selectedEdge;

    SharedPtr<Node> lightNode;

    void HandlePostRenderUpdate(StringHash, VariantMap&);
    void HandleMouseDown(StringHash, VariantMap&);
    void HandleKeyDown(StringHash, VariantMap&);

    lEditor& operator=(const lEditor&)
    {};
};