#pragma once


#include "GUI/Elements/Window.h"


class WindowVariables : public lWindow
{
    OBJECT(WindowVariables);

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