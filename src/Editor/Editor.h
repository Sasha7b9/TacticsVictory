#pragma once


#include "Game/Objects/Plane.h"
#include "Game/Objects/Terrain.h"


class tvEditor : public Object
{
    OBJECT(tvEditor);
public:
    tvEditor(Context *context);
    void Run();

private:

    SharedPtr<tvTerrain> terrain;
    tvPlane currentPlane;

    void HandlePostRenderUpdate(StringHash eventType, VariantMap &eventData);

    tvEditor& operator=(const tvEditor&)
    {};
};