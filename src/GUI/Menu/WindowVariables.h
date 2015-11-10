#pragma once


#include "GUI/Elements/Window.h"


class WindowVariables : public lWindow
{
    URHO3D_OBJECT(WindowVariables, lWindow);

public:
    WindowVariables(Context *context);

    void SetVar(float *var, char *title);
    void AddFunctionFloat(char *title, pFuncFV funcRead, pFuncVF funcWrite);

private:
    float *var = nullptr;
    char *title = nullptr;

    SharedPtr<Label> label;
    SharedPtr<GovernorFloat> governor;
};