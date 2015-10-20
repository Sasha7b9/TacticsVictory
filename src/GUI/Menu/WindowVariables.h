#pragma once


#include "GUI/Elements/Window.h"


class vWindowVariables : public vWindow
{
    OBJECT(vWindowVariables);

public:
    vWindowVariables(Context *context);

    void SetVar(float *var, char *title);
    void AddFunctionFloat(char *title, pFuncFV funcRead, pFuncVF funcWrite);

private:
    float *var = nullptr;
    char *title = nullptr;

    SharedPtr<vLabel> label;
    SharedPtr<vGovernorFloat> governor;
};