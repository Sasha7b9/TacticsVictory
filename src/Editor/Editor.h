#pragma once


#include "Game/Objects/Plane.h"
#include "Game/Objects/Terrain.h"


class vEditor : public Object
{
    OBJECT(vEditor);
public:
    vEditor(Context *context);
    void Run();

private:

    SharedPtr<vTerrain> terrain;
    vPlane currentPlane;

    void HandlePostRenderUpdate(StringHash eventType, VariantMap &eventData);

    vEditor& operator=(const vEditor&)
    {};
};