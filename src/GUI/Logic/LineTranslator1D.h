#pragma once


class LineTranslator1D : public UObject
{
    OBJECT(LineTranslator1D);

public:

    enum State
    {
        State_PointStart,
        State_PointFinish,
        State_MoveToFinish,
        State_MoveToStart
    };

    LineTranslator1D(int start, int finish, float speed, State startPosition);

    int Update(float dT);
    void Toggle();
    State GetState()
    {
        return state;
    }

private:
    LineTranslator1D& operator=(const LineTranslator1D&)
    {};

    float position = 0.0f;
    float start = 0.0f;
    float finish = 0.0f;
    float speed = 0.0f;
    State state = State_PointStart;
    float currentSpeed = 0.0f;
};