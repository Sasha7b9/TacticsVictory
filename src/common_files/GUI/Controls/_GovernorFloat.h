/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "GUI/Controls/_WindowRTS.h"


enum CellType
{
    CellType_Static,
    CellType_Digit,
    CellType_Sign
};


URHO3D_EVENT(E_GOVERNORCELLCHANGED, GovernorCellChanged)
{
    URHO3D_PARAM(P_ELEMENT, Element);
    URHO3D_PARAM(P_SYMBOL, Symbol);
}


class GovernorCell : public WindowRTS
{
    URHO3D_OBJECT(GovernorCell, WindowRTS);

public:
    GovernorCell(Context *context = TheContext);

    static void RegisterObject(Context *context = TheContext);

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
    SharedPtr<Text> label;
    char symbol = 0;
    bool mouseIsDown = false;
    bool mouseOver = false;
    int delta = 0;
    IntVector2 posCursor;
    bool selected = false;
    CellType type;

    void ChangeValue(int delta);
    void SetSymbolWithEvent(char symbol);

    DEFAULT_MEMBERS(GovernorCell);
};



class GovernorFloat : public WindowRTS
{
    URHO3D_OBJECT(GovernorFloat, WindowRTS);

public:
    GovernorFloat(Context *context = TheContext);

    static void RegisterObject(Context *context = TheContext);

    virtual void Update(float timeStep);

    void SetFunctionFloat(char *title, pFuncFV funcRead, pFuncVF funcWrite);

    void HandleGovernorCellChanged(StringHash eventType, VariantMap& eventData);
    void HandleHoverButtonBegin(StringHash eventType, VariantMap& eventData);
    void HandleHoverButtonEnd(StringHash eventType, VariantMap& eventData);

private:
    Vector<SharedPtr<GovernorCell> > cells;
    SharedPtr<Button> buttonDown;
    SharedPtr<Label> label;
    int numCells = 11;
    pFuncFV funcRead = nullptr; //-V122
    pFuncVF funcWrite = nullptr; //-V122
    char *title = nullptr; //-V122
    bool valueChanged = false;

    void WriteValue(float value);
    void GetOrderAndMantiss(float value, int *order, int *maintiss);
    void WriteMantiss(int mantiss);
    void WriteOrder(int order);
    float GetValue();

    DEFAULT_MEMBERS(GovernorFloat);
};
