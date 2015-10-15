#pragma once


class tvLineTranslator2D : public Object
{
    OBJECT(tvLineTranslator2D);

public:

    enum State
    {
        State_PointStart,
        State_PointFinish,
        State_MoveToFinish,
        State_MoveToStart
    };

    tvLineTranslator2D(const IntVector2 &start, const IntVector2 &finish, float speed, State startPosition);

    IntVector2 Update(float dT);
    void Toggle();

private:
    tvLineTranslator2D& operator=(const tvLineTranslator2D&)
    {};

    SharedPtr<tvLineTranslator1D> translatorX;
    SharedPtr<tvLineTranslator1D> translatorY;
};