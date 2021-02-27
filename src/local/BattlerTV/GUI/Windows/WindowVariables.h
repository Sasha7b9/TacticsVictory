// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/Window_.h"


class GovernorFloat;


class WindowVariables : public WindowT
{
    URHO3D_OBJECT(WindowVariables, WindowT);

public:
    WindowVariables(Context *context = TheContext);

    void SetVar(float *var, char *title);
    void AddFunctionFloat(char *title, pFuncFV funcRead, pFuncVF funcWrite);

private:
    float *var = nullptr; //-V122
    char *title = nullptr; //-V122

    SharedPtr<Label> label;
    SharedPtr<GovernorFloat> governor;
};
