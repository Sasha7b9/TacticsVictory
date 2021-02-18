// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/_TWindow.h"


class Tank;


class WindowTarget : public TWindow
{
    URHO3D_OBJECT(WindowTarget, TWindow);

public:
    WindowTarget(Context *context = TheContext);
    void AddTank(Tank *tank);

public:
    void HandleSetTexture(StringHash, VariantMap&);
};
