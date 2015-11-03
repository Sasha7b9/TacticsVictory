#pragma once


#include "Game/Objects/Tank.h"
#include "Game/PathIndicator.h"


class lScene : public Object
{
    OBJECT(lScene)

public:
    lScene(Context *context = gContext);

    static void RegisterObject(Context *context = gContext);

    void Update();
    void Create();

private:
    lScene& operator=(const lScene&)
    {};

    Vector<SharedPtr<lTank>> tanks;
    lPathIndicator pathIndicator;

    void RegisterObjects();

    void HandleMouseDown(StringHash, VariantMap&);
};