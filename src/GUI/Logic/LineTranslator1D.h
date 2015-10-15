#pragma once


class tvLineTranslator1D : public Object
{
    OBJECT(tvLineTranslator1D);

public:

    enum State
    {
        State_PointStart,
        State_PointFinish,
        State_MoveToFinish,
        State_MoveToStart
    };

    tvLineTranslator1D(int start, int finish, float speed, State startPosition);

    int Update(float dT);
    void Toggle();

private:
    tvLineTranslator1D& operator=(const tvLineTranslator1D&)
    {};

    float position = 0.0f;
    float start = 0.0f;
    float finish = 0.0f;
    float speed = 0.0f;
    State state = State_PointStart;
    float currentSpeed = 0.0f;
};