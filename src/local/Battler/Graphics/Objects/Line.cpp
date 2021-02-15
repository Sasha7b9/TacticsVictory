// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdafx.h>
#include "Line.h"



Line Line::ZERO = Line();


Line::Line(const Vector3 &start_, const Vector3 &end_)
{
    start = start_;
    end = end_;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Line::IsEquals(const Line &line)
{
    return start == line.start && end == line.end;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Line::IsZero()
{
    return start == Vector3::ZERO && end == Vector3::ZERO;
}
