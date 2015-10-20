#pragma once


#include "GUI/Elements/Window.h"


class lWindowVariables : public lWindow
{
    OBJECT(lWindowVariables);

public:
    lWindowVariables(Context *context);

    void SetVar(float *var, char *title);
    void AddFunctionFloat(char *title, pFuncFV funcRead, pFuncVF funcWrite);

private:
    float *var = nullptr;
    char *title = nullptr;

    SharedPtr<lLabel> label;
    SharedPtr<lGovernorFloat> governor;
};