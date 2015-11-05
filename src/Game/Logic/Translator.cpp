#include <stdafx.h>


#include "Translator.h"
#include "Core/Math.h"


void Translator::Set(const Vector3 &start, const Vector3 &end, float speed)
{
    this->end = end;
    currentPos = start;
    
    distance = (end - start).Length();

    this->speed = (end - start) / distance * speed;

    absSpeed = speed;
}

Vector3 Translator::Update(float dT, bool *inMovingState)
{
    currentPos += dT * speed;
    distance -= dT * absSpeed;

    *inMovingState = distance > 0.0f;

    if(!*inMovingState)
    {
        currentPos = end;
        speed = Vector3::ZERO;
    }

    return currentPos;
}