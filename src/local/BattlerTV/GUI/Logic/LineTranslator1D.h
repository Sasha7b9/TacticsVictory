// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once



class LineTranslator1D : public Object
{
    URHO3D_OBJECT(LineTranslator1D, Object);

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
    State GetState() { return state; }

private:
    float position = 0.0f;
    float start = 0.0f;
    float finish = 0.0f;
    float speed = 0.0f;
    State state = State_PointStart;
    float currentSpeed = 0.0f;

    DEFAULT_MEMBERS(LineTranslator1D);
};
