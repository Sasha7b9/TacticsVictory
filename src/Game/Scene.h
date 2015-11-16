#pragma once


#include "Game/Objects/Units/Tank/Tank.h"
#include "Game/Path/PathIndicator.h"


class lScene : public Object
{
    URHO3D_OBJECT(lScene, Object);

public:
    lScene(Context *context = gContext);
    ~lScene();

    static void RegisterObject(Context *context = gContext);

    void Update(float timeStep);
    void Create();

    void SetSelected(Tank *node, bool selected);
    Tank* GetSelected();

private:
    lScene& operator=(const lScene&)
    {};

    PathIndicator pathIndicator;

    void RegisterObjects();

    void HandleMouseDown(StringHash, VariantMap&);
    void ProcessMouseLeft();
    void ProcessMouseRight();
};