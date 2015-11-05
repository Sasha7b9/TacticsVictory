#pragma once


#include "GUI/Elements/Window.h"


enum CellType
{
    CellType_Static,
    CellType_Digit,
    CellType_Sign
};


EVENT(E_GOVERNORCELLCHANGED, GovernorCellChanged)
{
    PARAM(P_ELEMENT, Element);
    PARAM(P_SYMBOL, Symbol);
}


class vGovernorCell : public lWindow
{
    OBJECT(vGovernorCell);

public:
    vGovernorCell(Context *context = gContext);

    static void RegisterObject(Context *context = gContext);

    void SetSymbol(char symbol);
    char GetSymbol();
    void SetSelected();
    void SetNormal();
    void SetType(CellType type_)    { type = type_; };

    void HandleHoverBegin(StringHash eventType, VariantMap& eventData);
    void HandleHoverEnd(StringHash eventType, VariantMap& eventData);
    void HandleMouseDown(StringHash eventType, VariantMap& eventData);
    void HandleMouseUp(StringHash eventType, VariantMap& eventData);
    void HandleMouseMove(StringHash eventType, VariantMap& eventData);

private:
    vGovernorCell& operator=(const vGovernorCell&)
    {};

    void ChangeValue(int delta);
    void SetSymbolWithEvent(char symbol);

    SharedPtr<Urho3D::Text> label;
    char symbol = 0;
    bool mouseIsDown = false;
    bool mouseOver = false;
    int delta = 0;
    UIntVector2 posCursor;
    bool selected = false;
    CellType type;
};


class GovernorFloat : public lWindow
{
    OBJECT(GovernorFloat);

public:
    GovernorFloat(Context *context = gContext);

    static void RegisterObject(Context *context = gContext);

    virtual void Update(float timeStep);

    void SetFunctionFloat(char *title, pFuncFV funcRead, pFuncVF funcWrite);

    void HandleGovernorCellChanged(StringHash eventType, VariantMap& eventData);
    void HandleHoverButtonBegin(StringHash eventType, VariantMap& eventData);
    void HandleHoverButtonEnd(StringHash eventType, VariantMap& eventData);

private:
    GovernorFloat& operator=(const GovernorFloat&)
    {};

    void WriteValue(float value);
    void GetOrderAndMantiss(float value, int *order, int *maintiss);
    void WriteMantiss(int mantiss);
    void WriteOrder(int order);
    float GetValue();

    Vector<SharedPtr<vGovernorCell> > cells;
    SharedPtr<Urho3D::Button> buttonDown;
    SharedPtr<Label> label;
    int numCells = 11;
    pFuncFV funcRead = nullptr;
    pFuncVF funcWrite = nullptr;
    char *title = nullptr;
    float valueChanged = false;
};