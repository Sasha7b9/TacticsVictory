// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/Window_.h"


class Tank;


class WindowTarget : public TWindow
{
    URHO3D_OBJECT(WindowTarget, TWindow);

public:

    WindowTarget(Context *context = TheContext);

    void AddTank(Tank *tank);

private:

    static const int WIDTH = 500;
    static const int HEIGHT = 300;
};
