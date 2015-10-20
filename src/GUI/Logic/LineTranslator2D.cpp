#include <stdafx.h>


#include "LineTranslator2D.h"
#include "GUI/Logic/LineTranslator1D.h"


lLineTranslator2D::lLineTranslator2D(const IntVector2 &start, const IntVector2 &finish, float speed, State startPosition) :
    Object(gContext)
{
    translatorX = new lLineTranslator1D(start.x_, finish.x_, speed, (lLineTranslator1D::State)startPosition);
    translatorY = new lLineTranslator1D(start.y_, finish.y_, speed, (lLineTranslator1D::State)startPosition);
}

void lLineTranslator2D::Toggle()
{
    translatorX->Toggle();
    translatorY->Toggle();
}

IntVector2 lLineTranslator2D::Update(float dT)
{
    return IntVector2(translatorX->Update(dT), translatorY->Update(dT));
}