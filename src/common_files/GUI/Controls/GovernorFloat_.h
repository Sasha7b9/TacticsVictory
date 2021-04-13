// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/Window_.h"


URHO3D_EVENT(E_GOVERNORCELLCHANGED, GovernorCellChanged)
{
    URHO3D_PARAM(P_ELEMENT, Element);
    URHO3D_PARAM(P_SYMBOL, Symbol);
}


class GovernorCell : public WindowT
{
    URHO3D_OBJECT(GovernorCell, WindowT);

public:

    struct Type { enum E {
        Static,
        Digit,
        Sign
    }; };

    GovernorCell(Context *);
    static void RegisterObject();

    void SetSymbol(char symbol);
    char GetSymbol();
    void SetSelected();
    void SetNormal();
    void SetType(Type::E type_)    { type = type_; };

    void HandlerHoverBegin(StringHash eventType, VariantMap& eventData);
    void HandlerHoverEnd(StringHash eventType, VariantMap& eventData);
    void HandlerMouseDown(StringHash eventType, VariantMap& eventData);
    void HandlerMouseUp(StringHash eventType, VariantMap& eventData);
    void HandlerMouseMove(StringHash eventType, VariantMap& eventData);

private:
    SharedPtr<Text> label;
    char symbol = 0;
    bool mouseIsDown = false;
    bool mouseOver = false;
    int delta = 0;
    IntVector2 posCursor;
    bool selected = false;
    Type::E type = Type::Static;

    void ChangeValue(int delta);
    void SetSymbolWithEvent(char symbol);
};



class GovernorFloat : public WindowT
{
    URHO3D_OBJECT(GovernorFloat, WindowT);

public:
    GovernorFloat(Context *);
    static void RegisterObject();

    virtual void Update(float timeStep);

    void SetFunctionFloat(char *title, pFuncFV funcRead, pFuncVF funcWrite);

    void HandlerGovernorCellChanged(StringHash eventType, VariantMap& eventData);
    void HandlerHoverButtonBegin(StringHash eventType, VariantMap& eventData);
    void HandlerHoverButtonEnd(StringHash eventType, VariantMap& eventData);

private:
    Vector<SharedPtr<GovernorCell> > cells;
    SharedPtr<Button> buttonDown;
    SharedPtr<Label> label;
    int numCells = 11;
    pFuncFV funcRead = nullptr;
    pFuncVF funcWrite = nullptr;
    char *title = nullptr;
    bool valueChanged = false;

    void WriteValue(float value);
    void GetOrderAndMantiss(float value, int *order, int *maintiss);
    void WriteMantiss(int mantiss);
    void WriteOrder(int order);
    float GetValue();
};
