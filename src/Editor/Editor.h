#pragma once


#include "Game/Objects/Plane.h"
#include "Game/Objects/Terrain.h"


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

    SharedPtr<Node> lightNode;

    void HandlePostRenderUpdate(StringHash, VariantMap&);
    void HandleMouseDown(StringHash, VariantMap&);
    void HandleKeyDown(StringHash, VariantMap&);

    lEditor& operator=(const lEditor&)
    {};
};