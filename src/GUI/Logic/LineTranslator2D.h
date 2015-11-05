#pragma once


class LineTranslator2D : public Object
{
    OBJECT(LineTranslator2D);

public:

    enum State
    {
        State_PointStart,
        State_PointFinish,
        State_MoveToFinish,
        State_MoveToStart
    };

    LineTranslator2D(const UIntVector2 &start, const UIntVector2 &finish, float speed, State startPosition);

    UIntVector2 Update(float dT);
    void Toggle();
    State GetState();

private:
    LineTranslator2D& operator=(const LineTranslator2D&)
    {};

    SharedPtr<LineTranslator1D> translatorX;
    SharedPtr<LineTranslator1D> translatorY;
};