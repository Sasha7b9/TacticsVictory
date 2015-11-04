#include <stdafx.h>


#include "LineTranslator2D.h"
#include "GUI/Logic/LineTranslator1D.h"


LineTranslator2D::LineTranslator2D(const UIntVector2 &start, const UIntVector2 &finish, float speed, State startPosition) :
    Object(gContext)
{
    translatorX = new LineTranslator1D(start.x_, finish.x_, speed, (LineTranslator1D::State)startPosition);
    translatorY = new LineTranslator1D(start.y_, finish.y_, speed, (LineTranslator1D::State)startPosition);
}

void LineTranslator2D::Toggle()
{
    translatorX->Toggle();
    translatorY->Toggle();
}

UIntVector2 LineTranslator2D::Update(float dT)
{
    int x = translatorX->Update(dT);
    int y = translatorY->Update(dT);

    return UIntVector2(x, y);
}

LineTranslator2D::State LineTranslator2D::GetState()
{
    return (State)translatorX->GetState();
}
