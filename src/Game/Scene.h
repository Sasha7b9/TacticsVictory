#pragma once


#include "Game/Objects/Tank.h"
#include "Game/PathIndicator.h"


class Scene : public UObject
{
    OBJECT(Scene)

public:
    Scene(UContext *context = gContext);

    static void RegisterObject(UContext *context = gContext);

    void Update();
    void Create();

private:
    Scene& operator=(const Scene&)
    {};

    Vector<SharedPtr<Tank>> tanks;
    PathIndicator pathIndicator;

    void RegisterObjects();

    void HandleMouseDown(StringHash, VariantMap&);
};