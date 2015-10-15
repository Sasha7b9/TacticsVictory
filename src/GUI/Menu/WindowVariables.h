#pragma once


class tvWindowVariables : public tvWindow
{
    OBJECT(tvWindowVariables);

public:
    tvWindowVariables(Context *context);

    void SetVar(float *var, char *title);
    void AddFunctionFloat(char *title, pFuncFV funcRead, pFuncVF funcWrite);

private:
    float *var = nullptr;
    char *title = nullptr;

    SharedPtr<tvLabel> label;
    SharedPtr<tvGovernorFloat> governor;
};