#pragma once


#include "Game/Objects/Tank.h"
#include "Game/PathIndicator.h"
#include "Game/Path/Path.h"


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
    lPath path;

    void HandleMouseDown(StringHash, VariantMap&);
};