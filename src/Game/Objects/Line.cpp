#include <stdafx.h>


#include "Line.h"


lLine lLine::ZERO = lLine();

lLine::lLine(const Vector3 &start_, const Vector3 &end_)
{
    start = start_;
    end = end_;
}

bool lLine::IsEquals(const lLine &line)
{
    return start == line.start && end == line.end;
}

bool lLine::IsZero()
{
    return start == Vector3::ZERO && end == Vector3::ZERO;
}
