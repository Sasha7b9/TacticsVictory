#pragma once


class vLineTranslator1D : public Object
{
    OBJECT(vLineTranslator1D);

public:

    enum State
    {
        State_PointStart,
        State_PointFinish,
        State_MoveToFinish,
        State_MoveToStart
    };

    vLineTranslator1D(int start, int finish, float speed, State startPosition);

    int Update(float dT);
    void Toggle();

private:
    vLineTranslator1D& operator=(const vLineTranslator1D&)
    {};

    float position = 0.0f;
    float start = 0.0f;
    float finish = 0.0f;
    float speed = 0.0f;
    State state = State_PointStart;
    float currentSpeed = 0.0f;
};