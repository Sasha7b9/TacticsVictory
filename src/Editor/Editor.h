#pragma once


#include "Game/Objects/Plane.h"
#include "Game/Objects/Terrain.h"


class lEditor : public Object
{
    OBJECT(lEditor);
public:
    lEditor(Context *context);
    void Run();

private:
    lPlane currentPlane;

    void HandlePostRenderUpdate(StringHash eventType, VariantMap &eventData);
    void HandleKeyDown(StringHash eventType, VariantMap& eventData);
    void HandleMouseDown(StringHash eventType, VariantMap& eventData);

    lEditor& operator=(const lEditor&)
    {};
};