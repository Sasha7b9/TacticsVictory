#include <stdafx.h>


tvLineTranslator1D::tvLineTranslator1D(int start_, int finish_, float speed_, State startPosition) :
    Object(gContext),
    start((float)start_), finish((float)finish_), speed(fabs(speed_))
{
    state = startPosition;

    position = startPosition == State_PointStart ? start : finish;
}

void tvLineTranslator1D::Toggle()
{
    if(state == State_MoveToFinish || state == State_MoveToStart)
    {
        return;
    }

    if(state == State_PointStart)
    {
        speed = fabs(speed) * (finish < start ? -1.0f : 1.0f);
        position = start;
        state = State_MoveToFinish;
    }

    if(state == State_PointFinish)
    {
        speed = fabs(speed) * (start < finish ? -1.0f : 1.0f);
        position = finish;
        state = State_MoveToStart;
    }
}

int tvLineTranslator1D::Update(float dT)
{
    if(state == State_PointStart)
    {
        return (int)start;
    }
    if(state == State_PointFinish)
    {
        return (int)finish;
    }

    position += speed * dT;

    if(Math::PointsAreLocatedOneAfterAnother(start, position, finish))
    {
        return (int)position;
    }

    if(state == State_MoveToFinish)
    {
        position = finish;
        state = State_PointFinish;
    }
    else
    {
        position = start;
        state = State_PointStart;
    }

    return (int)position;
}