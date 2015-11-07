#pragma once


#include "Game/Objects/Units/Tank/Tank.h"
#include "Game/Path/PathIndicator.h"


class Scene : public Object
{
    OBJECT(Scene)

public:
    Scene(Context *context = gContext);
    ~Scene();

    static void RegisterObject(Context *context = gContext);

    void Update(float timeStep);
    void Create();

    void SetSelected(Tank *node, bool selected);
    Tank* GetSelected();

private:
    Scene& operator=(const Scene&)
    {};

    PathIndicator pathIndicator;

    void RegisterObjects();

    void HandleMouseDown(StringHash, VariantMap&);
};