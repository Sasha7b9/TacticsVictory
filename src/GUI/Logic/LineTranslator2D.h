#pragma once


class vLineTranslator2D : public Object
{
    OBJECT(vLineTranslator2D);

public:

    enum State
    {
        State_PointStart,
        State_PointFinish,
        State_MoveToFinish,
        State_MoveToStart
    };

    vLineTranslator2D(const IntVector2 &start, const IntVector2 &finish, float speed, State startPosition);

    IntVector2 Update(float dT);
    void Toggle();

private:
    vLineTranslator2D& operator=(const vLineTranslator2D&)
    {};

    SharedPtr<vLineTranslator1D> translatorX;
    SharedPtr<vLineTranslator1D> translatorY;
};