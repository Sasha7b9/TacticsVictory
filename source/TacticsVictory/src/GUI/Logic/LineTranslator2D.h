#pragma once


#include "LineTranslator1D.h"


class LineTranslator2D : public Object
{
    URHO3D_OBJECT(LineTranslator2D, Object);

public:

    enum State
    {
        State_PointStart,
        State_PointFinish,
        State_MoveToFinish,
        State_MoveToStart
    };

    LineTranslator2D(const IntVector2 &start, const IntVector2 &finish, float speed, State startPosition);

    IntVector2 Update(float dT);
    void Toggle();
    State GetState();

private:
    LineTranslator2D& operator=(const LineTranslator2D&)
    {};

    SharedPtr<LineTranslator1D> translatorX;
    SharedPtr<LineTranslator1D> translatorY;
};