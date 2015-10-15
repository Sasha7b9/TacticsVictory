#pragma once


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


class GovernorCell : public tvWindow
{
    OBJECT(GovernorCell);

public:
    GovernorCell(Context *context);

    static void RegisterObject(Context *context);

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
    GovernorCell& operator=(const GovernorCell&)
    {};

    void ChangeValue(int delta);
    void SetSymbolWithEvent(char symbol);

    SharedPtr<Text> label;
    char symbol = 0;
    bool mouseIsDown = false;
    bool mouseOver = false;
    int delta = 0;
    IntVector2 posCursor;
    bool selected = false;
    CellType type;
};


class tvGovernorFloat : public tvWindow
{
    OBJECT(tvGovernorFloat);

public:
    tvGovernorFloat(Context *context);

    static void RegisterObject(Context *context);

    virtual void Update(float timeStep);

    void SetFunctionFloat(char *title, pFuncFV funcRead, pFuncVF funcWrite);

    void HandleGovernorCellChanged(StringHash eventType, VariantMap& eventData);
    void HandleHoverButtonBegin(StringHash eventType, VariantMap& eventData);
    void HandleHoverButtonEnd(StringHash eventType, VariantMap& eventData);

private:
    tvGovernorFloat& operator=(const tvGovernorFloat&)
    {};

    void WriteValue(float value);
    void GetOrderAndMantiss(float value, int *order, int *maintiss);
    void WriteMantiss(int mantiss);
    void WriteOrder(int order);
    float GetValue();

    Vector<SharedPtr<GovernorCell> > cells;
    SharedPtr<Button> buttonDown;
    SharedPtr<tvLabel> label;
    int numCells = 11;
    pFuncFV funcRead = nullptr;
    pFuncVF funcWrite = nullptr;
    char *title = nullptr;
    float valueChanged = false;
};