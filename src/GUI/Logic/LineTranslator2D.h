#pragma once


class lLineTranslator2D : public Object
{
    OBJECT(lLineTranslator2D);

public:

    enum State
    {
        State_PointStart,
        State_PointFinish,
        State_MoveToFinish,
        State_MoveToStart
    };

    lLineTranslator2D(const IntVector2 &start, const IntVector2 &finish, float speed, State startPosition);

    IntVector2 Update(float dT);
    void Toggle();
    State GetState();

private:
    lLineTranslator2D& operator=(const lLineTranslator2D&)
    {};

    SharedPtr<lLineTranslator1D> translatorX;
    SharedPtr<lLineTranslator1D> translatorY;
};