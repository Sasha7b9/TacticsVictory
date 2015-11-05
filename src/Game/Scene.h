#pragma once


#include "Game/Objects/Tank.h"
#include "Game/Path/PathIndicator.h"


class Scene : public Object
{
    OBJECT(Scene)

public:
    Scene(Context *context = gContext);
    ~Scene();

    static void RegisterObject(Context *context = gContext);

    void Update();
    void Create();

    void SetSelected(Tank *node, bool selected);
    Tank* GetSelected();

private:
    Scene& operator=(const Scene&)
    {};

    Vector<SharedPtr<Tank>> tanks;
    PathIndicator pathIndicator;

    void RegisterObjects();

    void HandleMouseDown(StringHash, VariantMap&);
};