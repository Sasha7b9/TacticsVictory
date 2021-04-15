// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/Control_.h"


class GovernorFloat;


class WindowVariables : public Control
{
    URHO3D_OBJECT(WindowVariables, Control);

public:
    WindowVariables();

    void SetVar(float *var, char *title);
    void AddFunctionFloat(char *title, pFuncFV funcRead, pFuncVF funcWrite);

private:
    float *var = nullptr;
    char *title = nullptr;

    SharedPtr<Label> label;
    SharedPtr<GovernorFloat> governor;
};
