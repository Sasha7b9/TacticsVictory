#pragma once


#include "Game/Objects/Tank.h"


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

    bool Raycast(float maxDistance, Vector3 &hitPos, Drawable*& hitDrawable);
};