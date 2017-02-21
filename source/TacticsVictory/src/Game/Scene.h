#pragma once


#include "Game/Objects/Units/Tank/Tank.h"
#include "Game/Path/PathIndicator.h"


class SceneRTS : public Object
{
    URHO3D_OBJECT(SceneRTS, Object);

public:
    SceneRTS(Context *context = gContext);
    ~SceneRTS();

    static void RegisterObject(Context *context = gContext);

    void Update(float timeStep);
    void Create();

    void SetSelected(Tank *node, bool selected);
    Tank* GetSelected();

private:
    SceneRTS& operator=(const SceneRTS&)
    {};

    PathIndicator pathIndicator;

    void RegisterObjects();

    void HandleMouseDown(StringHash, VariantMap&);
    void ProcessMouseLeft();
    void ProcessMouseRight();
};